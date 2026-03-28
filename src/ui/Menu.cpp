/**
 * @file Menu.cpp
 * @brief Implementation of the Menu class.
 */

#include "ui/Menu.h"
#include <iostream>
#include <limits>

Menu::Menu() : parser(nullptr), engine(nullptr), dataLoaded(false), assignmentGenerated(false) {}

Menu::~Menu() {
    delete engine;
    delete parser;
}

void Menu::displayMenu() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Conference Assignment System" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " 1. Load CSV file" << std::endl;
    std::cout << " 2. List submissions" << std::endl;
    std::cout << " 3. List reviewers" << std::endl;
    std::cout << " 4. Show parameters" << std::endl;
    std::cout << " 5. Generate assignment" << std::endl;
    std::cout << " 6. Risk analysis" << std::endl;
    std::cout << " 0. Exit" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " Option: ";
}

void Menu::loadFile() {
    std::string filepath;
    std::cout << "Enter the path to the CSV file: ";
    std::cin >> filepath;

    // Clean up previous state
    delete engine;
    engine = nullptr;
    delete parser;
    parser = nullptr;
    dataLoaded = false;
    assignmentGenerated = false;

    parser = new CsvParser(filepath);

    if (parser->parse()) {
        dataLoaded = true;
        std::cout << "\nFile loaded successfully!" << std::endl;
        std::cout << "  Submissions: " << parser->getSubmissions().size() << std::endl;
        std::cout << "  Reviewers:   " << parser->getReviewers().size() << std::endl;
    } else {
        std::cerr << "Failed to load file." << std::endl;
        delete parser;
        parser = nullptr;
    }
}

void Menu::listSubmissions() const {
    if (!dataLoaded) {
        std::cout << "No data loaded. Please load a CSV file first (option 1)." << std::endl;
        return;
    }

    const auto& submissions = parser->getSubmissions();

    std::cout << "\n--- Submissions (" << submissions.size() << ") ---" << std::endl;
    for (const auto& s : submissions) {
        std::cout << "  ID: " << s.getId()
                  << " | Title: " << s.getTitle()
                  << " | Authors: " << s.getAuthors()
                  << " | Primary: " << s.getPrimaryTopic();
        if (s.getSecondaryTopic() != -1)
            std::cout << " | Secondary: " << s.getSecondaryTopic();
        std::cout << std::endl;
    }
}

void Menu::listReviewers() const {
    if (!dataLoaded) {
        std::cout << "No data loaded. Please load a CSV file first (option 1)." << std::endl;
        return;
    }

    const auto& reviewers = parser->getReviewers();

    std::cout << "\n--- Reviewers (" << reviewers.size() << ") ---" << std::endl;
    for (const auto& r : reviewers) {
        std::cout << "  ID: " << r.getId()
                  << " | Name: " << r.getName()
                  << " | Primary: " << r.getPrimaryExpertise();
        if (r.getSecondaryExpertise() != -1)
            std::cout << " | Secondary: " << r.getSecondaryExpertise();
        std::cout << std::endl;
    }
}

void Menu::showParameters() const {
    if (!dataLoaded) {
        std::cout << "No data loaded. Please load a CSV file first (option 1)." << std::endl;
        return;
    }

    const Config& config = parser->getConfig();

    std::cout << "\n--- Parameters ---" << std::endl;
    std::cout << "  Min Reviews Per Submission: " << config.getMinReviewsPerSubmission() << std::endl;
    std::cout << "  Max Reviews Per Reviewer:   " << config.getMaxReviewsPerReviewer() << std::endl;
    std::cout << "  Generate Assignments Mode:  " << config.getGenerateAssignments() << std::endl;
    std::cout << "  Risk Analysis:              " << config.getRiskAnalysis() << std::endl;
    std::cout << "  Output File:                " << config.getOutputFileName() << std::endl;
}

void Menu::generateAssignment() {
    if (!dataLoaded) {
        std::cout << "No data loaded. Please load a CSV file first (option 1)." << std::endl;
        return;
    }

    const Config& config = parser->getConfig();

    // Create a new engine each time
    delete engine;
    engine = new AssignmentEngine(parser->getSubmissions(), parser->getReviewers(), config);

    int flow = engine->solveBaseAssignment();
    int required = engine->getRequiredFlow();
    assignmentGenerated = true;

    std::cout << "\n--- Assignment Results ---" << std::endl;
    std::cout << "  Mode: " << config.getGenerateAssignments() << std::endl;
    std::cout << "  Computed flow: " << flow << " / " << required << std::endl;

    if (engine->hasValidAssignment()) {
        std::cout << "  Status: Valid assignment found!" << std::endl;
    } else {
        std::cout << "  Status: Could not assign all reviews." << std::endl;
    }

    // Display assignments
    const auto& assignments = engine->getAssignments();
    std::cout << "\n  Assignments (" << assignments.size() << "):" << std::endl;
    for (const auto& a : assignments) {
        std::cout << "    Reviewer " << a.reviewerId
                  << " -> Submission " << a.submissionId
                  << " (Topic " << a.topic << ")" << std::endl;
    }

    // Display missing reviews
    const auto& missingReviews = engine->getMissingReviews();
    if (!missingReviews.empty()) {
        std::cout << "\n  Missing Reviews (" << missingReviews.size() << "):" << std::endl;
        for (const auto& m : missingReviews) {
            std::cout << "    Submission " << m.submissionId
                      << " (Topic " << m.topic << ") missing "
                      << m.missingReviews << " review(s)" << std::endl;
        }
    }

    // Write output file (unless mode 0, which suppresses reporting)
    if (config.getGenerateAssignments() != 0) {
        OutputWriter::writeAssignments(config.getOutputFileName(), assignments, missingReviews);
    } else {
        std::cout << "\n  GenerateAssignments = 0: assignment computed but not reported to file." << std::endl;
    }
}

void Menu::runRiskAnalysis() {
    if (!dataLoaded) {
        std::cout << "No data loaded. Please load a CSV file first (option 1)." << std::endl;
        return;
    }

    const Config& config = parser->getConfig();
    int riskLevel = config.getRiskAnalysis();

    if (riskLevel == 0) {
        std::cout << "Risk analysis is disabled in the configuration (RiskAnalysis = 0)." << std::endl;
        return;
    }

    if (riskLevel > 1) {
        std::cout << "Warning: Risk Analysis with K > 1 is not fully implemented." << std::endl;
        std::cout << "Running K = 1 analysis instead." << std::endl;
    }

    std::cout << "\nRunning risk analysis (K=1)... This may take a moment." << std::endl;

    RiskAnalyzer analyzer(parser->getSubmissions(), parser->getReviewers(), config);
    const auto& critical = analyzer.findCriticalReviewersForK1();

    std::cout << "\n--- Risk Analysis Results (K=1) ---" << std::endl;

    if (critical.empty()) {
        std::cout << "  No critical reviewers found." << std::endl;
        std::cout << "  The assignment remains valid even if any single reviewer is removed." << std::endl;
    } else {
        std::cout << "  Critical reviewers (" << critical.size() << "):" << std::endl;
        for (int id : critical) {
            std::cout << "    Reviewer " << id << std::endl;
        }
    }

    // Write risk analysis file
    std::string riskFile = "risk_" + config.getOutputFileName();
    OutputWriter::writeRiskAnalysis(riskFile, critical, riskLevel);
}

void Menu::run() {
    int option = -1;

    while (true) {
        displayMenu();

        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        switch (option) {
            case 1: loadFile(); break;
            case 2: listSubmissions(); break;
            case 3: listReviewers(); break;
            case 4: showParameters(); break;
            case 5: generateAssignment(); break;
            case 6: runRiskAnalysis(); break;
            case 0:
                std::cout << "Exiting. Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}
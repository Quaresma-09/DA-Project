/**
 * @file main.cpp
 * @brief Entry point for the Conference Assignment System.
 *
 * Supports two modes of operation:
 * - Interactive: Launches a CLI menu for manual operation.
 * - Batch: Processes a CSV file directly and outputs results.
 *   Usage: myProg -b input.csv output.csv
 */

#include <iostream>
#include <string>
#include "parser/CsvParser.h"
#include "core/AssignmentEngine.h"
#include "core/RiskAnalyzer.h"
#include "core/OutputWriter.h"
#include "ui/Menu.h"

/**
 * @brief Runs the program in batch mode.
 *
 * Parses the input file, generates assignments, and optionally runs
 * risk analysis. All output is written to the specified output file.
 * Error messages are directed to stderr.
 *
 * @param inputFile Path to the input CSV file.
 * @param outputFile Path for the output file (overrides config).
 * @return 0 on success, 1 on failure.
 *
 * @complexity O(V * E^2) for the max-flow computation.
 */
int runBatchMode(const std::string& inputFile, const std::string& outputFile) {
    CsvParser parser(inputFile);

    if (!parser.parse()) {
        std::cerr << "Error: Failed to parse file " << inputFile << std::endl;
        return 1;
    }

    const auto& submissions = parser.getSubmissions();
    const auto& reviewers = parser.getReviewers();
    const Config& config = parser.getConfig();

    std::cout << "Loaded " << submissions.size() << " submissions and "
              << reviewers.size() << " reviewers." << std::endl;

    // Generate assignments
    AssignmentEngine engine(submissions, reviewers, config);
    int flow = engine.solveBaseAssignment();
    int required = engine.getRequiredFlow();

    std::cout << "Flow: " << flow << " / " << required << std::endl;

    if (engine.hasValidAssignment()) {
        std::cout << "Valid assignment found." << std::endl;
    } else {
        std::cout << "Could not assign all reviews." << std::endl;
    }

    // Write assignment output (only if GenerateAssignments != 0)
    if (config.getGenerateAssignments() != 0) {
        OutputWriter::writeAssignments(outputFile, engine.getAssignments(), engine.getMissingReviews());
    } else {
        std::cout << "GenerateAssignments = 0: assignment computed but not reported." << std::endl;
    }

    // Run risk analysis if enabled in the config
    int riskLevel = config.getRiskAnalysis();
    if (riskLevel > 0) {
        if (riskLevel > 1) {
            std::cerr << "Warning: Risk Analysis with K > 1 is not implemented. "
                      << "Running K = 1 analysis instead." << std::endl;
        }

        std::cout << "Running risk analysis (K=1)..." << std::endl;

        RiskAnalyzer analyzer(submissions, reviewers, config);
        const auto& critical = analyzer.findCriticalReviewersForK1();

        if (critical.empty()) {
            std::cout << "No critical reviewers found." << std::endl;
        } else {
            std::cout << "Found " << critical.size() << " critical reviewer(s)." << std::endl;
        }

        // Append risk analysis to the output file (or write new if mode 0)
        if (config.getGenerateAssignments() != 0) {
            OutputWriter::appendRiskAnalysis(outputFile, critical, riskLevel);
        } else {
            OutputWriter::writeRiskAnalysis(outputFile, critical, riskLevel);
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    // Batch mode: myProg -b input.csv output.csv
    if (argc >= 4 && std::string(argv[1]) == "-b") {
        std::string inputFile = argv[2];
        std::string outputFile = argv[3];
        return runBatchMode(inputFile, outputFile);
    }

    // Interactive mode
    Menu menu;
    menu.run();

    return 0;
}
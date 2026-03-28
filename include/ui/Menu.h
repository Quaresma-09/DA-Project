/**
 * @file Menu.h
 * @brief Header file for the Menu class.
 *
 * Provides a command-line interactive interface for the conference
 * assignment system, exposing all implemented functionalities.
 */

#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include "parser/CsvParser.h"
#include "core/AssignmentEngine.h"
#include "core/RiskAnalyzer.h"
#include "core/OutputWriter.h"

#include <string>

/**
 * @class Menu
 * @brief Interactive CLI menu for the conference assignment system.
 *
 * Allows users to load CSV files, inspect parsed data, generate
 * reviewer-submission assignments, and run risk analysis.
 */
class Menu {
private:
    CsvParser* parser;
    AssignmentEngine* engine;
    bool dataLoaded;
    bool assignmentGenerated;

    /**
     * @brief Displays the main menu options.
     */
    void displayMenu() const;

    /**
     * @brief Loads and parses a CSV file.
     */
    void loadFile();

    /**
     * @brief Lists all parsed submissions.
     */
    void listSubmissions() const;

    /**
     * @brief Lists all parsed reviewers.
     */
    void listReviewers() const;

    /**
     * @brief Displays the current configuration parameters.
     */
    void showParameters() const;

    /**
     * @brief Generates the reviewer-submission assignment.
     */
    void generateAssignment();

    /**
     * @brief Runs risk analysis (K=1) and reports critical reviewers.
     */
    void runRiskAnalysis();

public:

    /**
     * @brief Constructor.
     */
    Menu();

    /**
     * @brief Destructor. Cleans up allocated resources.
     */
    ~Menu();

    /**
     * @brief Starts the interactive menu loop.
     */
    void run();
};

#endif //DA_PROJECT_MENU_H
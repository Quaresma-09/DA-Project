/**
 * @file CsvParser.h
 * @brief Header file for the CsvParser class.
 * * This file contains the declaration of the CsvParser class, which is responsible
 * for reading, cleaning, and validating data from conference CSV files.
 */

#ifndef DA_PROJECT_CSVPARSER_H
#define DA_PROJECT_CSVPARSER_H

#include <string>
#include <vector>
#include <unordered_set>
#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"

/**
 * @class CsvParser
 * @brief Handles the extraction of data from a formatted CSV file.
 * * The class processes four main sections: #Submissions, #Reviewers, #Parameters, and #Control.
 * It ensures data integrity by checking for duplicate IDs and ignoring comments or empty lines.
 */
class CsvParser {
private:
    std::string filename;             ///< Path to the input CSV file.
    std::vector<Submission> submissions; ///< Collection of parsed submissions.
    std::vector<Reviewer> reviewers;     ///< Collection of parsed reviewers.
    Config config;                       ///< Configuration parameters parsed from the file.

    std::unordered_set<int> submissionIds; ///< Helper set to ensure submission IDs are unique.
    std::unordered_set<int> reviewerIds;   ///< Helper set to ensure reviewer IDs are unique.

    /**
     * @brief Removes leading and trailing whitespace from a string.
     * @param str The string to be trimmed.
     * @return A new string without surrounding whitespace.
     */
    std::string trim(const std::string& str);

    /**
     * @brief Splits a CSV line into tokens based on the ',' delimiter.
     * @param line The raw line from the CSV file.
     * @return A vector of strings containing the individual columns.
     */
    std::vector<std::string> splitCsvLine(const std::string& line);

    /**
     * @brief Removes comments starting with '#' from a line.
     * @param line The raw line to be cleaned.
     * @return The line content before the '#' character.
     */
    std::string removeComments(const std::string& line);

public:
    /**
     * @brief Constructor for the CsvParser.
     * @param filename The path to the CSV file to be processed.
     */
    explicit CsvParser(std::string filename);

    /**
     * @brief Orchestrates the parsing process of the CSV file.
     * * Reads the file line by line, identifies sections, and populates the
     * corresponding data structures (Submissions, Reviewers, Config).
     * * @return true if the file was parsed successfully without critical errors,
     * false if the file could not be opened or has severe formatting issues.
     */
    bool parse();

    /**
     * @brief Provides access to the list of parsed submissions.
     * @return A constant reference to a vector of Submission objects.
     */
    const std::vector<Submission>& getSubmissions() const { return submissions; }

    /**
     * @brief Provides access to the list of parsed reviewers.
     * @return A constant reference to a vector of Reviewer objects.
     */
    const std::vector<Reviewer>& getReviewers() const { return reviewers; }

    /**
     * @brief Provides access to the global configuration parameters.
     * @return A constant reference to the Config object.
     */
    const Config& getConfig() const { return config; }
};

#endif //DA_PROJECT_CSVPARSER_H
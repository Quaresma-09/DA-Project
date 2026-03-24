/**
 * @file CsvParser.cpp
 * @brief Implementation of the CsvParser class logic.
 */

#include "parser/CsvParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

CsvParser::CsvParser(std::string filename) : filename(std::move(filename)) {}

/**
 * @brief Cleans strings by removing whitespace and quotes.
 * Useful for handling CSV fields that might have inconsistent spacing.
 */
std::string CsvParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n\"");
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Strips comments from the input line.
 * This allows the parser to ignore everything after the '#' character 
 * within data lines.
 */
std::string CsvParser::removeComments(const std::string& line) {
    size_t pos = line.find('#');
    if (pos != std::string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

/**
 * @brief Custom CSV splitter that handles quoted fields.
 * Iterates through the line character by character to ensure commas 
 * inside quotes don't break the tokenization.
 */
std::vector<std::string> CsvParser::splitCsvLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;
    
    for (char c : line) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(trim(current));
            current.clear();
        } else {
            current += c;
        }
    }
    tokens.push_back(trim(current));
    return tokens;
}

/**
 * @brief Main parsing loop using a State Machine approach.
 * * The method identifies headers (e.g., #Submissions) to switch states and 
 * determines how to process subsequent lines based on the current state.
 * Includes error handling for duplicated IDs and malformed integers.
 */
bool CsvParser::parse() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open file " << filename << std::endl;
        return false;
    }

    std::string line;
    /// Internal states to track which section of the CSV is being read.
    enum State { NONE, SUBMISSIONS, REVIEWERS, PARAMETERS, CONTROL };
    State currentState = NONE;

    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;

        std::string trimmedLine = trim(line);
        
        // Section detection logic
        if (trimmedLine == "#Submissions") { currentState = SUBMISSIONS; continue; }
        if (trimmedLine == "#Reviewers") { currentState = REVIEWERS; continue; }
        if (trimmedLine == "#Parameters") { currentState = PARAMETERS; continue; }
        if (trimmedLine == "#Control") { currentState = CONTROL; continue; }
        if (trimmedLine == "#") { currentState = NONE; continue; }

        // Skip comments and empty lines
        std::string cleanLine = removeComments(line);
        if (trim(cleanLine).empty()) continue;

        std::vector<std::string> tokens = splitCsvLine(cleanLine);

        try {
            if (currentState == SUBMISSIONS) {
                if (tokens.size() < 5) continue;
                int id = std::stoi(tokens[0]);
                
                // Duplicate ID validation
                if (submissionIds.find(id) != submissionIds.end()) {
                    std::cerr << "Error in line " << lineNum << ": Submission ID duplicate (" << id << ")." << std::endl;
                    return false;
                }
                submissionIds.insert(id);

                int primary = std::stoi(tokens[4]);
                int secondary = (tokens.size() >= 6 && !tokens[5].empty()) ? std::stoi(tokens[5]) : -1;
                
                submissions.emplace_back(id, tokens[1], tokens[2], tokens[3], primary, secondary);
            } 
            else if (currentState == REVIEWERS) {
                if (tokens.size() < 4) continue;
                int id = std::stoi(tokens[0]);

                if (reviewerIds.find(id) != reviewerIds.end()) {
                    std::cerr << "Error in line " << lineNum << ": Reviewer ID duplicate (" << id << ")." << std::endl;
                    return false;
                }
                reviewerIds.insert(id);

                int primary = std::stoi(tokens[3]);
                int secondary = (tokens.size() >= 5 && !tokens[4].empty()) ? std::stoi(tokens[4]) : -1;

                reviewers.emplace_back(id, tokens[1], tokens[2], primary, secondary);
            }
            else if (currentState == PARAMETERS || currentState == CONTROL) {
                if (tokens.size() < 2) continue;
                std::string key = tokens[0];
                std::string value = tokens[1];

                // Map CSV keys to Config object methods
                if (key == "MinReviewsPerSubmission") config.setMinReviewsPerSubmission(std::stoi(value));
                else if (key == "MaxReviewsPerReviewer") config.setMaxReviewsPerReviewer(std::stoi(value));
                else if (key == "GenerateAssignments") config.setGenerateAssignments(std::stoi(value));
                else if (key == "RiskAnalysis") config.setRiskAnalysis(std::stoi(value));
                else if (key == "OutputFileName") config.setOutputFileName(value);
            }
        } catch (const std::exception& e) {
            std::cerr << "Formatting error on line " << lineNum << ": " << cleanLine << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}
/**
 * @file Config.h
 * @brief Header file for the Config class.
 * * This file defines the Config class, which stores the execution parameters
 * and constraints parsed from the configuration file.
 */

#ifndef DA_PROJECT_CONFIG_H
#define DA_PROJECT_CONFIG_H

#include <string>

/**
 * @class Config
 * @brief Manages global configuration settings for the conference assignment system.
 * * This class stores numerical constraints (min/max reviews) and operational flags
 * (assignment mode and risk analysis) that dictate how the network flow and
 * analysis algorithms should behave.
 */
class Config {
private:
    int minReviewsPerSubmission = 0;    ///< Minimum number of reviews required for each paper.
    int maxReviewsPerReviewer = 0;      ///< Maximum number of papers a single reviewer can handle.
    int generateAssignments = 0;       ///< Flag for assignment mode (0: None, 1: Primary only, 2: Mixed, 3: Full).
    int riskAnalysis = 0;              ///< Flag to enable (1) or disable (0) the risk analysis algorithm.
    std::string outputFileName = "output.csv"; ///< Name of the file where results will be saved.

public:
    /**
     * @brief Default constructor for Config.
     * Initializes all parameters to their default values (zero or empty).
     */
    Config() = default;

    /**
     * @brief Gets the minimum reviews per submission.
     * @return The required number of reviews per paper.
     */
    int getMinReviewsPerSubmission() const { return minReviewsPerSubmission; }

    /**
     * @brief Gets the maximum reviews per reviewer.
     * @return The maximum capacity of each reviewer.
     */
    int getMaxReviewsPerReviewer() const { return maxReviewsPerReviewer; }

    /**
     * @brief Gets the assignment generation mode.
     * @return An integer representing the chosen assignment strategy.
     */
    int getGenerateAssignments() const { return generateAssignments; }

    /**
     * @brief Gets the risk analysis status.
     * @return 1 if enabled, 0 if disabled.
     */
    int getRiskAnalysis() const { return riskAnalysis; }

    /**
     * @brief Gets the designated output filename.
     * @return A string containing the filename (default is "output.csv").
     */
    std::string getOutputFileName() const { return outputFileName; }

    /**
     * @brief Sets the minimum reviews per submission.
     * @param val The new minimum value.
     */
    void setMinReviewsPerSubmission(int val) { minReviewsPerSubmission = val; }

    /**
     * @brief Sets the maximum reviews per reviewer.
     * @param val The new maximum capacity.
     */
    void setMaxReviewsPerReviewer(int val) { maxReviewsPerReviewer = val; }

    /**
     * @brief Sets the assignment generation mode.
     * @param val The flag value (typically 1, 2, or 3).
     */
    void setGenerateAssignments(int val) { generateAssignments = val; }

    /**
     * @brief Sets the risk analysis status.
     * @param val 1 to enable, 0 to disable.
     */
    void setRiskAnalysis(int val) { riskAnalysis = val; }

    /**
     * @brief Sets the name for the output file.
     * @param val The new filename string.
     */
    void setOutputFileName(const std::string& val) { outputFileName = val; }
};

#endif //DA_PROJECT_CONFIG_H
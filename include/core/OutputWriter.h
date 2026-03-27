/**
 * @file OutputWriter.h
 * @brief Header file for the OutputWriter class.
 *
 * Responsible for formatting and writing assignment results and risk
 * analysis reports to CSV files following the project specification.
 */

#ifndef DA_PROJECT_OUTPUTWRITER_H
#define DA_PROJECT_OUTPUTWRITER_H

#include "core/AssignmentEngine.h"

#include <string>
#include <vector>

/**
 * @class OutputWriter
 * @brief Writes assignment and risk analysis results to CSV files.
 *
 * Formats the output according to the project specification, including
 * sorted assignment views and risk analysis reporting.
 */
class OutputWriter {
public:

    /**
     * @brief Writes assignments and missing reviews to a CSV file.
     *
     * Output format follows Figures 2 and 3 of the specification:
     * - #SubmissionId,ReviewerId,Match (sorted by SubmissionId)
     * - #ReviewerId,SubmissionId,Match (sorted by ReviewerId)
     * - #Total: N
     * - #SubmissionId,Domain,MissingReviews (if any, sorted)
     *
     * @param filename The output file path.
     * @param assignments The list of computed assignments.
     * @param missingReviews The list of submissions with insufficient reviews.
     * @return true if successful, false otherwise.
     *
     * @complexity O(A log A + M) where A = assignments, M = missing reviews.
     */
    static bool writeAssignments(const std::string& filename,
                                 const std::vector<Assignment>& assignments,
                                 const std::vector<MissingReview>& missingReviews);

    /**
     * @brief Writes the risk analysis results to a file.
     *
     * Output format follows Figure 4 of the specification:
     * - #Risk Analysis: M
     * - Sorted list of critical reviewer IDs
     *
     * @param filename The output file path.
     * @param criticalReviewers Sorted vector of critical reviewer IDs.
     * @param riskLevel The risk analysis parameter value (K).
     * @return true if successful, false otherwise.
     *
     * @complexity O(C) where C = number of critical reviewers.
     */
    static bool writeRiskAnalysis(const std::string& filename,
                                  const std::vector<int>& criticalReviewers,
                                  int riskLevel);

    /**
     * @brief Appends risk analysis results to an existing output file.
     *
     * Used in batch mode to add risk analysis to the same output file.
     *
     * @complexity O(C)
     */
    static bool appendRiskAnalysis(const std::string& filename,
                                   const std::vector<int>& criticalReviewers,
                                   int riskLevel);
};

#endif //DA_PROJECT_OUTPUTWRITER_H
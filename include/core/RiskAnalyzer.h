/**
 * @file RiskAnalyzer.h
 * @brief Header file for the RiskAnalyzer class.
 *
 * Defines the risk analysis functionality that determines which
 * reviewers are critical to the assignment process.
 */

#ifndef DA_PROJECT_RISK_ANALYZER_H
#define DA_PROJECT_RISK_ANALYZER_H

#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"

#include <vector>

/**
 * @class RiskAnalyzer
 * @brief Analyzes the impact of removing reviewers from the assignment problem.
 *
 * For Risk Analysis with K = 1, each reviewer is removed one at a time
 * and the assignment problem is solved again. If the assignment becomes
 * invalid (i.e., max flow < required flow), that reviewer is critical.
 */
class RiskAnalyzer {
private:
    std::vector<Submission> submissions;   ///< Copy of the submissions list.
    std::vector<Reviewer> reviewers;       ///< Copy of the reviewers list.
    Config config;                         ///< Copy of the configuration.

public:

    /**
     * @brief Constructs the risk analyzer with the problem data.
     * @param submissions The list of submissions.
     * @param reviewers The list of reviewers.
     * @param config The configuration parameters.
     */
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Config& config);

    /**
     * @brief Finds all critical reviewers for the case K = 1.
     *
     * A reviewer is considered critical if removing that reviewer makes
     * it impossible to obtain a valid complete assignment (i.e., the
     * max flow drops below the required flow).
     *
     * @return A vector of reviewer IDs that are critical.
     *
     * @complexity O(R * V * E^2) where R = number of reviewers,
     *             V = vertices in the flow network, E = edges.
     */
    std::vector<int> findCriticalReviewersForK1() const;
};

#endif
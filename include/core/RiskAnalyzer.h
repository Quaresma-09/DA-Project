#ifndef DA_PROJECT_RISK_ANALYZER_H
#define DA_PROJECT_RISK_ANALYZER_H

#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"

#include <vector>

/**
 * @brief Analyzes the impact of removing reviewers from the assignment problem.
 *
 * This class is used for Risk Analysis with K = 1, where one reviewer
 * is removed at a time and the assignment problem is solved again to
 * determine whether that reviewer is critical.
 */
class RiskAnalyzer {
private:
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Config config;

public:

    /**
     * @brief Constructs the risk analyzer.
     */
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Config& config);

    /**
    * @brief Finds critical reviewers for the case K = 1.
    *
    * Each reviewer is removed individually and the assignment problem
    * is solved again to determine if a valid solution still exists.
    *
    * @complexity O(R * V * E^2)
    */
    std::vector<int> findCriticalReviewersForK1() const;
};

#endif
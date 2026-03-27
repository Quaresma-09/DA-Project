/**
 * @file RiskAnalyzer.cpp
 * @brief Implementation of the RiskAnalyzer class.
 */

#include "core/RiskAnalyzer.h"
#include "core/AssignmentEngine.h"

RiskAnalyzer::RiskAnalyzer(const std::vector<Submission>& submissions,
                           const std::vector<Reviewer>& reviewers,
                           const Config& config)
    : submissions(submissions),
      reviewers(reviewers),
      config(config) {}

std::vector<int> RiskAnalyzer::findCriticalReviewersForK1() const {
    std::vector<int> criticalReviewers;

    int numReviewers = static_cast<int>(reviewers.size());

    for (int i = 0; i < numReviewers; i++) {
        // Create a list of reviewers excluding reviewer i
        std::vector<Reviewer> filteredReviewers;
        filteredReviewers.reserve(numReviewers - 1);

        for (int j = 0; j < numReviewers; j++) {
            if (j != i) {
                filteredReviewers.push_back(reviewers[j]);
            }
        }

        // Solve the assignment problem without this reviewer
        AssignmentEngine engine(submissions, filteredReviewers, config);

        int flow = engine.solveBaseAssignment();
        int required = engine.getRequiredFlow();

        // If the flow drops below required, this reviewer is critical
        if (flow < required) {
            criticalReviewers.push_back(reviewers[i].getId());
        }
    }

    return criticalReviewers;
}

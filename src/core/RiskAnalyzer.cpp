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
        std::vector<Reviewer> filteredReviewers;
        filteredReviewers.reserve(numReviewers - 1);

        for (int j = 0; j < numReviewers; j++) {
            if (j != i) {
                filteredReviewers.push_back(reviewers[j]);
            }
        }

        AssignmentEngine engine(submissions, filteredReviewers, config);

        int flow = engine.solveBaseAssignment();
        int required = engine.getRequiredFlow();

        if (flow < required) {
            criticalReviewers.push_back(reviewers[i].getId());
        }
    }

    return criticalReviewers;
}
#ifndef DA_PROJECT_RISK_ANALYZER_H
#define DA_PROJECT_RISK_ANALYZER_H

#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"

#include <vector>

class RiskAnalyzer {
private:
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Config config;

public:
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Config& config);

    std::vector<int> findCriticalReviewersForK1() const;
};

#endif
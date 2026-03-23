#ifndef DA_PROJECT_ASSIGNMENT_ENGINE_H
#define DA_PROJECT_ASSIGNMENT_ENGINE_H

#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"
#include "graph/Graph.h"
#include "graph/MaxFlow.h"

#include <vector>

struct Assignment {
    int reviewerId;
    int submissionId;
    int topic;
};

struct MissingReview {
    int submissionId;
    int topic;
    int missingReviews;
};

class AssignmentEngine {
private:
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Config config;

    Graph graph;
    MaxFlow maxFlow;

    int source;
    int sink;
    int reviewerOffset;
    int submissionOffset;
    int totalNodes;
    int lastComputedFlow;

    std::vector<Assignment> assignments;
    std::vector<MissingReview> missingReviews;

    void initializeGraph();
    void buildBaseGraph();
    void extractAssignments();
    void calculateMissingReviews();

    bool isCompatible(const Reviewer& reviewer, const Submission& submission) const;
    int getReviewerNode(int reviewerIndex) const;
    int getSubmissionNode(int submissionIndex) const;
    int getReviewerIndexFromNode(int node) const;
    int getSubmissionIndexFromNode(int node) const;

public:
    AssignmentEngine(const std::vector<Submission>& submissions,
                     const std::vector<Reviewer>& reviewers,
                     const Config& config);

    int solveBaseAssignment();

    int getRequiredFlow() const;
    int getLastComputedFlow() const;
    bool hasValidAssignment() const;

    const std::vector<Assignment>& getAssignments() const;
    const std::vector<MissingReview>& getMissingReviews() const;
};

#endif
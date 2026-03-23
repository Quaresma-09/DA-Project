#include "core/AssignmentEngine.h"

AssignmentEngine::AssignmentEngine(const std::vector<Submission>& submissions,
                                   const std::vector<Reviewer>& reviewers,
                                   const Config& config)
    : submissions(submissions),
      reviewers(reviewers),
      config(config),
      graph(),
      maxFlow(),
      source(0),
      sink(0),
      reviewerOffset(1),
      submissionOffset(1 + static_cast<int>(reviewers.size())),
      totalNodes(0),
      lastComputedFlow(0) {
    sink = submissionOffset + static_cast<int>(submissions.size());
    totalNodes = sink + 1;
    graph = Graph(totalNodes);
}

void AssignmentEngine::initializeGraph() {
    graph = Graph(totalNodes);
    lastComputedFlow = 0;
}

bool AssignmentEngine::isCompatible(const Reviewer& reviewer, const Submission& submission) const {
    return reviewer.getPrimaryExpertise() == submission.getPrimaryTopic();
}

int AssignmentEngine::getReviewerNode(int reviewerIndex) const {
    return reviewerOffset + reviewerIndex;
}

int AssignmentEngine::getSubmissionNode(int submissionIndex) const {
    return submissionOffset + submissionIndex;
}

void AssignmentEngine::buildBaseGraph() {
    int numReviewers = static_cast<int>(reviewers.size());
    int numSubmissions = static_cast<int>(submissions.size());

    int maxReviewsPerReviewer = config.getMaxReviewsPerReviewer();
    int minReviewsPerSubmission = config.getMinReviewsPerSubmission();

    for (int i = 0; i < numReviewers; i++) {
        graph.addEdge(source, getReviewerNode(i), maxReviewsPerReviewer);
    }

    for (int i = 0; i < numReviewers; i++) {
        for (int j = 0; j < numSubmissions; j++) {
            if (isCompatible(reviewers[i], submissions[j])) {
                graph.addEdge(getReviewerNode(i), getSubmissionNode(j), 1);
            }
        }
    }

    for (int i = 0; i < numSubmissions; i++) {
        graph.addEdge(getSubmissionNode(i), sink, minReviewsPerSubmission);
    }
}

int AssignmentEngine::solveBaseAssignment() {
    initializeGraph();
    buildBaseGraph();
    lastComputedFlow = maxFlow.edmondsKarp(graph, source, sink);
    return lastComputedFlow;
}

int AssignmentEngine::getRequiredFlow() const {
    return static_cast<int>(submissions.size()) * config.getMinReviewsPerSubmission();
}

int AssignmentEngine::getLastComputedFlow() const {
    return lastComputedFlow;
}

bool AssignmentEngine::hasValidAssignment() const {
    return lastComputedFlow == getRequiredFlow();
}
/**
 * @file AssignmentEngine.cpp
 * @brief Implementation of the AssignmentEngine class.
 */

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
    assignments.clear();
    missingReviews.clear();
}

bool AssignmentEngine::isCompatible(const Reviewer& reviewer, const Submission& submission) const {
    // According to T2.4, Modes 2 and 3 do not need to be implemented, 
    // only the theoretical approach needs to be outlined in the presentation.
    // Thus, we only implement Mode 0 and 1 (Primary Domains only).
    
    if (config.getGenerateAssignments() > 1) {
        // Fallback to Primary-only since general mode isn't explicitly implemented here
    }

    return reviewer.getPrimaryExpertise() == submission.getPrimaryTopic();
}

int AssignmentEngine::getMatchTopic(const Reviewer& reviewer, const Submission& submission) const {
    // Since only Primary Domains are considered, the match topic is always the primary topic.
    return submission.getPrimaryTopic();
}

int AssignmentEngine::getReviewerNode(int reviewerIndex) const {
    return reviewerOffset + reviewerIndex;
}

int AssignmentEngine::getSubmissionNode(int submissionIndex) const {
    return submissionOffset + submissionIndex;
}

int AssignmentEngine::getReviewerIndexFromNode(int node) const {
    return node - reviewerOffset;
}

int AssignmentEngine::getSubmissionIndexFromNode(int node) const {
    return node - submissionOffset;
}

void AssignmentEngine::buildBaseGraph() {
    int numReviewers = static_cast<int>(reviewers.size());
    int numSubmissions = static_cast<int>(submissions.size());

    int maxReviewsPerReviewer = config.getMaxReviewsPerReviewer();

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
        graph.addEdge(getSubmissionNode(i), sink, config.getMinReviewsPerSubmission());
    }
}

void AssignmentEngine::extractAssignments() {
    std::vector<std::vector<Edge>>& adj = graph.getAdj();

    for (int i = 0; i < static_cast<int>(reviewers.size()); i++) {
        int reviewerNode = getReviewerNode(i);

        for (const Edge& edge : adj[reviewerNode]) {
            if (edge.to >= submissionOffset && edge.to < sink && edge.flow == 1) {
                int submissionIndex = getSubmissionIndexFromNode(edge.to);

                Assignment assignment;
                assignment.reviewerId = reviewers[i].getId();
                assignment.submissionId = submissions[submissionIndex].getId();
                assignment.topic = getMatchTopic(reviewers[i], submissions[submissionIndex]);

                assignments.push_back(assignment);
            }
        }
    }
}

void AssignmentEngine::calculateMissingReviews() {
    std::vector<std::vector<Edge>>& adj = graph.getAdj();
    int minReviewsPerSubmission = config.getMinReviewsPerSubmission();

    for (int i = 0; i < static_cast<int>(submissions.size()); i++) {
        int submissionNode = getSubmissionNode(i);
        int receivedReviews = 0;

        for (const Edge& edge : adj[submissionNode]) {
            if (edge.to == sink) {
                receivedReviews = edge.flow;
                break;
            }
        }

        int missing = minReviewsPerSubmission - receivedReviews;

        if (missing > 0) {
            MissingReview missingReview;
            missingReview.submissionId = submissions[i].getId();
            missingReview.topic = submissions[i].getPrimaryTopic();
            missingReview.missingReviews = missing;

            missingReviews.push_back(missingReview);
        }
    }
}

int AssignmentEngine::solveBaseAssignment() {
    initializeGraph();
    buildBaseGraph();
    lastComputedFlow = maxFlow.edmondsKarp(graph, source, sink);
    extractAssignments();
    calculateMissingReviews();
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

const std::vector<Assignment>& AssignmentEngine::getAssignments() const {
    return assignments;
}

const std::vector<MissingReview>& AssignmentEngine::getMissingReviews() const {
    return missingReviews;
}
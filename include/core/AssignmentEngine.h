#ifndef DA_PROJECT_ASSIGNMENT_ENGINE_H
#define DA_PROJECT_ASSIGNMENT_ENGINE_H

#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"
#include "graph/Graph.h"
#include "graph/MaxFlow.h"

#include <vector>

/**
 * @brief Represents an assignment between a reviewer and a submission.
 */
struct Assignment {
    int reviewerId;
    int submissionId;
    int topic;
};

/**
 * @brief Represents missing reviews for a submission.
 */
struct MissingReview {
    int submissionId;
    int topic;
    int missingReviews;
};

/**
 * @brief Builds and solves the reviewer assignment problem using max-flow.
 *
 * Constructs a flow network where reviewers are matched to submissions
 * based on primary expertise, and computes a valid assignment using
 * the Edmonds-Karp algorithm.
 */
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

    /**
     * @brief Initializes the graph structure.
     *
     * @complexity O(V)
     */
    void initializeGraph();

    /**
     * @brief Builds the base flow network.
     *
     * @complexity O(R * S)
     */
    void buildBaseGraph();

    /**
     * @brief Extracts assignments from the computed flow.
     *
     * @complexity O(R * S)
     */
    void extractAssignments();

    /**
     * @brief Calculates missing reviews for each submission.
     *
     * @complexity O(S)
     */
    void calculateMissingReviews();

    /**
 * @brief Checks if a reviewer is compatible with a submission.
 *
 * Compatibility is based on matching primary expertise and topic.
 */
    bool isCompatible(const Reviewer& reviewer, const Submission& submission) const;

    /**
     * @brief Returns the node index corresponding to a reviewer.
     */
    int getReviewerNode(int reviewerIndex) const;

    /**
     * @brief Returns the node index corresponding to a submission.
     */
    int getSubmissionNode(int submissionIndex) const;

    int getReviewerIndexFromNode(int node) const;
    int getSubmissionIndexFromNode(int node) const;

public:

    /**
     * @brief Constructs the assignment engine.
     */
    AssignmentEngine(const std::vector<Submission>& submissions,
                     const std::vector<Reviewer>& reviewers,
                     const Config& config);

    /**
     * @brief Solves the assignment problem using max-flow.
     *
     * @complexity Dominated by Edmonds-Karp: O(V * E^2)
     */
    int solveBaseAssignment();

    /**
     * @brief Returns the required total flow.
     */
    int getRequiredFlow() const;

    /**
     * @brief Returns the computed flow.
     */
    int getLastComputedFlow() const;

    /**
     * @brief Checks if a valid assignment exists.
     */
    bool hasValidAssignment() const;

    /**
     * @brief Returns the computed assignments.
     */
    const std::vector<Assignment>& getAssignments() const;

    /**
     * @brief Returns missing reviews for submissions.
     */
    const std::vector<MissingReview>& getMissingReviews() const;
};

#endif
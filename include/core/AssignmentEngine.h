/**
 * @file AssignmentEngine.h
 * @brief Header file for the AssignmentEngine class.
 *
 * Defines the assignment engine that uses max-flow to compute
 * reviewer-submission assignments based on domain expertise.
 */

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
 * based on domain expertise, and computes a valid assignment using
 * the Edmonds-Karp algorithm. Supports different assignment modes:
 * - Mode 0/1: Primary domains only.
 * - Mode 2: Primary + Secondary submission domains, Primary reviewer expertise.
 * - Mode 3: All primary and secondary domains of both.
 *
 * @complexity O(V * E^2) for the max-flow computation.
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
     * @brief Builds the flow network based on the current assignment mode.
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
     * Uses the GenerateAssignments mode from the config to determine
     * which domains to consider for compatibility.
     *
     * @complexity O(1)
     */
    bool isCompatible(const Reviewer& reviewer, const Submission& submission) const;

    /**
     * @brief Determines the matched topic between a reviewer and submission.
     *
     * @complexity O(1)
     */
    int getMatchTopic(const Reviewer& reviewer, const Submission& submission) const;

    int getReviewerNode(int reviewerIndex) const;
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
     * @complexity O(V * E^2)
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
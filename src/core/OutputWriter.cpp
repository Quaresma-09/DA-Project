/**
 * @file OutputWriter.cpp
 * @brief Implementation of the OutputWriter class.
 */

#include "core/OutputWriter.h"
#include <fstream>
#include <iostream>
#include <algorithm>

bool OutputWriter::writeAssignments(const std::string& filename,
                                    const std::vector<Assignment>& assignments,
                                    const std::vector<MissingReview>& missingReviews) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    // Create sorted copies of assignments for the two views
    std::vector<Assignment> bySubmission = assignments;
    std::vector<Assignment> byReviewer = assignments;

    // Sort by submission ID (and reviewer ID as tiebreaker)
    std::sort(bySubmission.begin(), bySubmission.end(), [](const Assignment& a, const Assignment& b) {
        if (a.submissionId != b.submissionId) return a.submissionId < b.submissionId;
        return a.reviewerId < b.reviewerId;
    });

    // Sort by reviewer ID (and submission ID as tiebreaker)
    std::sort(byReviewer.begin(), byReviewer.end(), [](const Assignment& a, const Assignment& b) {
        if (a.reviewerId != b.reviewerId) return a.reviewerId < b.reviewerId;
        return a.submissionId < b.submissionId;
    });

    // View 1: by submission
    file << "#SubmissionId,ReviewerId,Match" << std::endl;
    for (const auto& a : bySubmission) {
        file << a.submissionId << ", " << a.reviewerId << ", " << a.topic << std::endl;
    }

    // View 2: by reviewer
    file << "#ReviewerId,SubmissionId,Match" << std::endl;
    for (const auto& a : byReviewer) {
        file << a.reviewerId << ", " << a.submissionId << ", " << a.topic << std::endl;
    }

    // Total
    file << "#Total: " << assignments.size() << std::endl;

    // Missing reviews (if any)
    if (!missingReviews.empty()) {
        std::vector<MissingReview> sortedMissing = missingReviews;
        std::sort(sortedMissing.begin(), sortedMissing.end(), [](const MissingReview& a, const MissingReview& b) {
            return a.submissionId < b.submissionId;
        });

        file << "#SubmissionId,Domain,MissingReviews" << std::endl;
        for (const auto& m : sortedMissing) {
            file << m.submissionId << ", " << m.topic << ", " << m.missingReviews << std::endl;
        }
    }

    file.close();
    std::cout << "Output written to " << filename << std::endl;
    return true;
}

bool OutputWriter::writeRiskAnalysis(const std::string& filename,
                                     const std::vector<int>& criticalReviewers,
                                     int riskLevel) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    std::vector<int> sorted = criticalReviewers;
    std::sort(sorted.begin(), sorted.end());

    file << "#Risk Analysis: " << riskLevel << std::endl;
    for (int i = 0; i < static_cast<int>(sorted.size()); i++) {
        if (i > 0) file << ", ";
        file << sorted[i];
    }
    file << std::endl;

    file.close();
    std::cout << "Risk analysis written to " << filename << std::endl;
    return true;
}

bool OutputWriter::appendRiskAnalysis(const std::string& filename,
                                      const std::vector<int>& criticalReviewers,
                                      int riskLevel) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for appending." << std::endl;
        return false;
    }

    std::vector<int> sorted = criticalReviewers;
    std::sort(sorted.begin(), sorted.end());

    file << "#Risk Analysis: " << riskLevel << std::endl;
    for (int i = 0; i < static_cast<int>(sorted.size()); i++) {
        if (i > 0) file << ", ";
        file << sorted[i];
    }
    file << std::endl;

    file.close();
    return true;
}
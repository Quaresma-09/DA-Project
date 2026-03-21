#ifndef DA_PROJECT_CONFIG_H
#define DA_PROJECT_CONFIG_H

#include <string>

class Config {
private:
    int minReviewsPerSubmission = 0;
    int maxReviewsPerReviewer = 0;
    int generateAssignments = 0; // 0, 1, 2, ou 3 [cite: 68-79]
    int riskAnalysis = 0;        // 0, 1, ou K [cite: 80-85]
    std::string outputFileName = "output.csv"; // Default

public:
    Config() = default;

    // Getters
    int getMinReviewsPerSubmission() const { return minReviewsPerSubmission; }
    int getMaxReviewsPerReviewer() const { return maxReviewsPerReviewer; }
    int getGenerateAssignments() const { return generateAssignments; }
    int getRiskAnalysis() const { return riskAnalysis; }
    std::string getOutputFileName() const { return outputFileName; }

    // Setters (para o parser preencher)
    void setMinReviewsPerSubmission(int val) { minReviewsPerSubmission = val; }
    void setMaxReviewsPerReviewer(int val) { maxReviewsPerReviewer = val; }
    void setGenerateAssignments(int val) { generateAssignments = val; }
    void setRiskAnalysis(int val) { riskAnalysis = val; }
    void setOutputFileName(const std::string& val) { outputFileName = val; }
};

#endif //DA_PROJECT_CONFIG_H
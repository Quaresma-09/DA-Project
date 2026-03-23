#ifndef DA_PROJECT_CSVPARSER_H
#define DA_PROJECT_CSVPARSER_H

#include <string>
#include <vector>
#include <unordered_set>
#include "model/Submission.h"
#include "model/Reviewer.h"
#include "model/Config.h"

class CsvParser {
private:
    std::string filename;
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Config config;

    std::unordered_set<int> submissionIds;
    std::unordered_set<int> reviewerIds;

    std::string trim(const std::string& str);
    std::vector<std::string> splitCsvLine(const std::string& line);
    std::string removeComments(const std::string& line);

public:
    explicit CsvParser(std::string filename);

    bool parse(); // Return false if there are critical errors

    // Getters
    const std::vector<Submission>& getSubmissions() const { return submissions; }
    const std::vector<Reviewer>& getReviewers() const { return reviewers; }
    const Config& getConfig() const { return config; }
};

#endif //DA_PROJECT_CSVPARSER_H
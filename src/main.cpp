#include <iostream>
#include "../include/parser/CsvParser.h"
#include "../include/graph/Graph.h"

int main() {
    std::cout << "=== Integration Test: Graph (M1 + M2) ===\n\n";

    // 1. Initialize your Parser (M1) and read the input file
    std::string filePath = "../data/input/input.csv";
    CsvParser parser(filePath);

    if (!parser.parse()) {
        std::cerr << "❌ Failed to process the CSV file. Check the errors above.\n";
        return 1;
    }

    // 2. Fetch the data extracted by the parser
    const Config& config = parser.getConfig();
    const auto& submissions = parser.getSubmissions();
    const auto& reviewers = parser.getReviewers();

    // 3. Initialize your teammate's Graph (M2)
    // The graph needs to know the total number of vertices.
    // We allocate 1000 nodes for this quick test.
    Graph myGraph(1000);

    // Dummy mapping (offsets) just for this test to avoid ID collisions
    // (e.g., Submission ID 1 vs Reviewer ID 1)
    int sourceNode = 0;
    int sinkNode = 1;
    int submissionOffset = 100;
    int reviewerOffset = 500;

    // 4. Test connecting the Source to the Submissions (Capacity = MinReviews)
    int minReviews = config.getMinReviewsPerSubmission();
    for (const auto& sub : submissions) {
        int mappedSubId = sub.getId() + submissionOffset;
        myGraph.addEdge(sourceNode, mappedSubId, minReviews);
    }
    std::cout << "✅ Edges 'Source -> Submissions' added to the graph!\n";

    // 5. Test connecting the Reviewers to the Sink (Capacity = MaxReviews)
    int maxReviews = config.getMaxReviewsPerReviewer();
    for (const auto& rev : reviewers) {
        int mappedRevId = rev.getId() + reviewerOffset;
        myGraph.addEdge(mappedRevId, sinkNode, maxReviews);
    }
    std::cout << "✅ Edges 'Reviewers -> Sink' added to the graph!\n";

    std::cout << "\nThe graph currently has " << myGraph.size() << " nodes allocated in memory.\n";
    std::cout << "Your data structures and parser fit perfectly with M2's code!\n";

    return 0;
}
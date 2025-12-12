#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>

struct Page {
    int id;
    std::string content;
};

class InvertedIndex {
public:
    void addPage(const Page& page) {
        // TODO: Implement according to 03_inverted_index.md
        // 1. Tokenize page.content
        // 2. For each word, add page.id to map
        // 3. Ensure uniqueness of page.id in the list
        (void)page;
    }

    std::vector<int> query(const std::vector<std::string>& words) {
        // TODO: Implement according to 03_inverted_index.md
        // 1. For each word, retrieve list of page IDs
        // 2. Compute intersection of all lists
        (void)words;
        return {};
    }
};

void run_test(const std::string& name, const std::vector<int>& actual, const std::vector<int>& expected) {
    if (actual == expected) {
        std::cout << "[PASS] " << name << std::endl;
    } else {
        std::cout << "[FAIL] " << name << " Expected: {";
        for (size_t i = 0; i < expected.size(); ++i) std::cout << expected[i] << (i < expected.size() - 1 ? "," : "");
        std::cout << "} Actual: {";
        for (size_t i = 0; i < actual.size(); ++i) std::cout << actual[i] << (i < actual.size() - 1 ? "," : "");
        std::cout << "}" << std::endl;
    }
}

int main() {
    InvertedIndex index;
    
    // Setup pages from derivation
    index.addPage({1, "A B"});
    index.addPage({2, "B C"});
    index.addPage({3, "D D"}); // Duplicate word test

    // Test 1: Single word query "B" -> {1, 2}
    run_test("Query B", index.query({"B"}), {1, 2});

    // Test 2: Multi word "A B" -> {1}
    run_test("Query A B", index.query({"A", "B"}), {1});

    // Test 3: Multi word "A C" -> {}
    run_test("Query A C", index.query({"A", "C"}), {});

    // Test 4: Single word "D" -> {3} (Test deduplication during add)
    run_test("Query D", index.query({"D"}), {3});

    // Test 5: Unknown word "X" -> {}
    run_test("Query X", index.query({"X"}), {});

    return 0;
}

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
private:
    std::map<std::string, std::vector<int>> index;

    // Helper to intersect two sorted vectors
    // TRACE: L1=[10, 30], L2=[10, 20] (From Derivation Step 15)
    // i=0, j=0. 10==10 -> Match. res=[10]. i=1, j=1.
    // i=1, j=1. 30>20 -> j++. j=2.
    // i=1, j=2. j at end. Stop.
    // Result: [10]
    std::vector<int> intersect(const std::vector<int>& v1, const std::vector<int>& v2) {
        std::vector<int> res;
        size_t i = 0, j = 0;
        while (i < v1.size() && j < v2.size()) {
            if (v1[i] < v2[j]) {
                i++;
            } else if (v1[i] > v2[j]) {
                j++;
            } else { // Equal
                res.push_back(v1[i]);
                i++;
                j++;
            }
        }
        return res;
    }

public:
    void addPage(const Page& page) {
        // TRACE: Page(10, "apple banana")
        // Token "apple": index["apple"] list empty. Add 10. List: [10]
        // Token "banana": index["banana"] list empty. Add 10. List: [10]
        // TRACE: Page(20, "banana cherry")
        // Token "banana": index["banana"] has [10]. 20 > 10. Add 20. List: [10, 20]
        // Token "cherry": index["cherry"] list empty. Add 20. List: [20]
        std::string current_word;
        
        auto process_word = [&](std::string& w) {
            if (w.empty()) return;
            // Add page.id to list if it's not the same as the last ones (to avoid duplicates for same page)
            std::vector<int>& list = index[w];
            // TRACE: Duplicate check from Derivation Step 37
            // If list is [40] and new ID is 40 -> 40 == 40, do NOT add.
            if (list.empty() || list.back() != page.id) {
                list.push_back(page.id);
            }
        };

        for (char c : page.content) {
            if (std::isalnum(c)) {
                current_word += std::tolower(c);
            } else {
                process_word(current_word);
                current_word.clear();
            }
        }
        process_word(current_word); // Process last word
    }

    std::vector<int> query(const std::vector<std::string>& words) {
        if (words.empty()) return {};

        std::vector<std::string> normalized_words;
        for (const auto& w : words) {
            std::string nw;
            for (char c : w) {
                if (std::isalnum(c)) nw += std::tolower(c);
            }
            if (!nw.empty()) normalized_words.push_back(nw);
        }

        if (normalized_words.empty()) return {};

        // Start with the list for the first word
        auto it = index.find(normalized_words[0]);
        if (it == index.end()) return {}; // First word not found -> Intersection empty
        std::vector<int> result = it->second;

        // Intersect with remaining words
        for (size_t i = 1; i < normalized_words.size(); ++i) {
            auto it2 = index.find(normalized_words[i]);
            if (it2 == index.end()) return {}; // Any word not found -> Intersection empty (since it's AND)
            
            result = intersect(result, it2->second);
            if (result.empty()) return {}; // Optimization
        }

        return result;
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
    
    // Setup pages from Derivation Step 01
    // P1_ID=10, P1_CONTENT="apple banana"
    index.addPage({10, "apple banana"});
    // P2_ID=20, P2_CONTENT="banana cherry"
    index.addPage({20, "banana cherry"});
    // P3_ID=30, P3_CONTENT="apple cherry"
    index.addPage({30, "apple cherry"});

    // Derivation Step 22: Query "apple" "banana" -> {10}
    run_test("Query apple banana", index.query({"apple", "banana"}), {10});

    // Derivation Step 33: Query "apple" "cherry" -> {30}
    run_test("Query apple cherry", index.query({"apple", "cherry"}), {30});

    // Derivation Step 34: Duplicate words "dog dog" (P4_ID=40)
    index.addPage({40, "dog dog"});
    // Query "dog" -> {40} (Unique ID check)
    run_test("Query dog", index.query({"dog"}), {40});

    // Derivation Step 22 (Variant): Query "banana" -> {10, 20}
    run_test("Query banana", index.query({"banana"}), {10, 20});

    // Unknown word
    run_test("Query X", index.query({"X"}), {});

    return 0;
}

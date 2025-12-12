#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

namespace StudentTest {

    // Strategy A: Maximize number of completed questions (Longest First)
    // Returns the number of completed questions.
    int strategy_longest_first(int K, std::vector<int> T) {
        // TODO: Implement Longest First Strategy
        // Sort T descending
        // Iterate and pick if <= K_rem
        return 0; 
    }

    // Strategy B: Maximize total amount of time used (Shortest First)
    // Returns the total time of completed questions.
    int strategy_shortest_first(int K, std::vector<int> T) {
        // TODO: Implement Shortest First Strategy
        // Sort T ascending
        // Iterate and pick if <= K_rem
        return 0;
    }

    void run_test_case(int K, std::vector<int> T, int expected_count_optimal, int expected_time_optimal) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Test Case: K=" << K << ", T=[";
        for (size_t i = 0; i < T.size(); ++i) std::cout << T[i] << (i < T.size() - 1 ? ", " : "");
        std::cout << "]" << std::endl;

        int count_a = strategy_longest_first(K, T);
        int time_b = strategy_shortest_first(K, T);

        std::cout << "  Strategy A (Count): " << count_a << " (Longest First)" << std::endl;
        std::cout << "  Strategy B (Time):  " << time_b << " (Shortest First)" << std::endl;
        
        // In derivation phase, we just observe the output vs manual expectations
        std::cout << "  Expected Optimal Count (A): " << expected_count_optimal << std::endl;
        std::cout << "  Expected Optimal Time (B):  " << expected_time_optimal << std::endl;
    }
}

int main() {
    // Axiomatic Counter-Examples derived in 09_student_test.md

    // Case 1: Proving Longest First is NOT optimal for Count
    // T = {10, 2, 2, 2}, K = 10
    // Longest First -> Pick 10 -> Count 1
    // Optimal (Shortest) -> Pick 2, 2, 2 -> Count 3
    StudentTest::run_test_case(10, {10, 2, 2, 2}, 3, 10);

    // Case 2: Proving Shortest First is NOT optimal for Time
    // T = {3, 8}, K = 10
    // Shortest First -> Pick 3 -> Time 3
    // Optimal -> Pick 8 -> Time 8
    StudentTest::run_test_case(10, {3, 8}, 1, 8);

    // Case 3: Another check
    // T = {5, 5, 10}, K = 10
    // Shortest -> 5, 5 -> Time 10
    // Optimal -> 10 -> Time 10 (Tie)
    StudentTest::run_test_case(10, {5, 5, 10}, 2, 10);

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

// Function to find the maximum sum of a subset with no consecutive elements
long long max_sum_no_adjacent(const vector<int>& nums) {
    // TODO: Implement the solution based on the derivation in 12_max_sum_no_adjacent.md
    // Remember: Use axiomatic derivation, do not memorize the solution.
    // Determine base cases, recurrence relation, and handle edge cases strictly.
    int n = nums.size();
    if ( n == 0 )
    {
        return 0;
    }
    if ( n == 1)
    {
        return nums[0];
    }

    long long best_2_back = 0; 
    long long best_1_back = nums[0];
    for ( int i = 1; i < n; i++)
    {
        long long best_here = std::max(
            best_2_back + nums[i],
            best_1_back
        );

        best_2_back  = best_1_back;
        best_1_back = best_here;
    }

    return best_1_back;
}

void test(const vector<int>& input, long long expected) {
    long long result = max_sum_no_adjacent(input);
    cout << "Input: {";
    for (size_t i = 0; i < input.size(); ++i) {
        cout << input[i] << (i < input.size() - 1 ? ", " : "");
    }
    cout << "} -> Expected: " << expected << ", Got: " << result;
    if (result == expected) {
        cout << " [PASS]" << endl;
    } else {
        cout << " [FAIL]" << endl;
    }
}

int main() {
    // Basic cases
    test({1, 2, 3}, 4);          // 1 + 3
    test({1, 20, 3}, 20);        // 20
    test({10, 20, 15}, 25);      // 10 + 15

    // Larger chains
    test({3, 2, 7, 10}, 13);     // 3 + 10
    test({3, 2, 5, 10, 7}, 15);  // 3 + 5 + 7

    // Edge cases
    test({}, 0);                 // Empty
    test({5}, 5);                // Single element
    test({5, 5}, 5);             // Two equal

    // Tricky cases (Parity traps)
    test({5, 5, 10, 100, 10, 5}, 110); // 5 + 100 + 5 (indices 0, 3, 5 - wait, 0(5), 2(10), 4(10)? No. 5, 100, 5 is indices 0, 3, 5? No.
                                       // Indices: 0:5, 1:5, 2:10, 3:100, 4:10, 5:5
                                       // Opt: 5(0) + 100(3) + 5(5) = 110. Indices 0, 3, 5 are separated by >1.
                                       // Is there better?
                                       // Odd pos (1 based): 1:5, 3:10, 5:10 -> 25.
                                       // Even pos: 2:5, 4:100, 6:5 -> 110.
                                       
    test({5, 5, 10, 40, 50, 35}, 80); // {5, 40, 35} = 80. {5, 50, 5} = 60.
                                      // Indices: 0:5, 1:5, 2:10, 3:40, 4:50, 5:35
                                      // Opt: 5(1) + 40(3) + 35(5) ? Indices 1, 3, 5 (0-based). No adjacent. Sum=80.

    return 0;
}

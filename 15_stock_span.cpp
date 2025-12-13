#include <iostream>
#include <vector>
#include <cassert>

// A[0..n-1] = prices → S[0..n-1] = spans
// S[i] = count of consecutive elements A[j] immediately before A[i] where A[j] ≤ A[i], including A[i]
// Example: A={6,3,4,5,2} → S={1,1,2,3,1}
// 
// JUMP-BASED SOLUTION (NO std::stack):
// Instead of stack, use S[j] to jump backward
// S[j] = span at j = number of elements ≤ A[j] before j
// If A[j] ≤ A[i], skip j and all elements in S[j] (they are also ≤ A[j] ≤ A[i])
// Jump: j = j - S[j]
std::vector<int> computeSpan(const std::vector<int>& A) {
    int n = A.size();
    std::vector<int> S(n);  // S[i] holds span, also used for jumping
    
    for (int i = 0; i < n; i++) {
        int j = i - 1;  // start immediately left of i
        
        // j=i-1: check A[j] > A[i]?
        // if not, jump by S[j] (skip elements known to be ≤ A[j])
        // repeat until stopper found or j < 0
        while (j >= 0 && A[j] <= A[i]) {
            j = j - S[j];  // JUMP: skip S[j] elements at once
            // j=2, S[2]=2 → j=0 (skipped indices 2,1)
            // j=1, S[1]=1 → j=0 (skipped index 1)
        }
        
        if (j < 0) {
            S[i] = i + 1;  // no stopper, span = all left elements + self
        } else {
            S[i] = i - j;  // stopper at j, span = distance from j to i
        }
    }
    
    return S;
}

void test_example() {
    std::vector<int> A = {6, 3, 4, 5, 2};
    std::vector<int> expected = {1, 1, 2, 3, 1};
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_example passed" << std::endl;
}

void test_ascending() {
    std::vector<int> A = {1, 2, 3, 4};
    std::vector<int> expected = {1, 2, 3, 4};
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_ascending passed" << std::endl;
}

void test_descending() {
    std::vector<int> A = {4, 3, 2, 1};
    std::vector<int> expected = {1, 1, 1, 1};
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_descending passed" << std::endl;
}

void test_plateau() {
    std::vector<int> A = {5, 5, 5, 5};
    std::vector<int> expected = {1, 2, 3, 4};  // ≤ means equal counts
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_plateau passed" << std::endl;
}

void test_single() {
    std::vector<int> A = {7};
    std::vector<int> expected = {1};
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_single passed" << std::endl;
}

void test_peak() {
    std::vector<int> A = {1, 2, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 1, 1};
    std::vector<int> result = computeSpan(A);
    assert(result == expected);
    std::cout << "test_peak passed" << std::endl;
}

int main() {
    test_example();
    test_ascending();
    test_descending();
    test_plateau();
    test_single();
    test_peak();
    return 0;
}

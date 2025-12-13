#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

// A[0..n-1] = prices → S[0..n-1] = spans
// S[i] = count of consecutive elements A[j] immediately before A[i] where A[j] ≤ A[i], including A[i]
// Example: A={6,3,4,5,2} → S={1,1,2,3,1}
std::vector<int> computeSpan(const std::vector<int>& A) {
    int n = A.size();
    std::vector<int> S(n);           // S[i] will hold span of A[i]
    std::stack<int> stk;             // stack of indices, not values 
    
    for (int i = 0; i < n; i++) {
        // TODO: Pop indices from stack while they are "useless" for future elements
        // Hint: A[stk.top()] ??? A[i] → what comparison?
        
        // TODO: Calculate S[i] using stack state
        // If stack empty: S[i] = ???
        // If stack not empty: S[i] = i - stk.top() or i - stk.top() - 1 or ???
        
        // TODO: Push current index onto stack
        // Why? Current index might be stopper for future elements
        while (!stk.empty() && A[stk.top()] <= A[i]) {
            stk.pop();
        }
        if (stk.empty()) {
            S[i] = i + 1;
        } else {
            S[i] = i - stk.top();
        }
        stk.push(i);
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

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

unsigned long long solve(int n, const vector<string>& grid) {
    // E1-E5 fix: use 0-indexed, size n, access 0..n-1
    vector<vector<unsigned long long>> dp(n, vector<unsigned long long>(n, 0));
    
    // E8 fix: check if start is blocked
    if (grid[0][0] == '+') return 0;
    dp[0][0] = 1;
    
    // E6 fix: initialize row 0 with block check
    for (int j = 1; j < n; j++) {
        if (grid[0][j] == '+') dp[0][j] = 0;
        else dp[0][j] = dp[0][j-1];
    }
    
    // E6 fix: initialize col 0 with block check
    for (int i = 1; i < n; i++) {
        if (grid[i][0] == '+') dp[i][0] = 0;
        else dp[i][0] = dp[i-1][0];
    }
    
    // E7 fix: check block before computing sum
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (grid[i][j] == '+') dp[i][j] = 0;
            else dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    
    // E5 fix: return dp[n-1][n-1] not dp[n][n]
    return dp[n-1][n-1];
}

void test_cases() {
    // Test Case 1: Example from derivation
    // ...
    // ...
    // ...
    // Output: 2
    assert(solve(3, {
        "...",
        ".+.",
        "..."
    }) == 2);
    cout << "Test Case 1 Passed" << endl;

    // Test Case 2: N=1, Start is '.'
    assert(solve(1, {"."}) == 1);
    cout << "Test Case 2 Passed" << endl;

    // Test Case 3: N=1, Start is '+'
    assert(solve(1, {"+"}) == 0);
    cout << "Test Case 3 Passed" << endl;

    // Test Case 4: N=2, All clear
    // ..
    // ..
    assert(solve(2, {
        "..",
        ".."
    }) == 2);
    cout << "Test Case 4 Passed" << endl;

    // Test Case 5: N=2, Path blocked
    // .+
    // ..
    assert(solve(2, {
        ".+",
        ".."
    }) == 1);
    cout << "Test Case 5 Passed" << endl;

    // Test Case 6: Start blocked
    assert(solve(3, {
        "+..",
        "...",
        "..."
    }) == 0);
    cout << "Test Case 6 Passed" << endl;

    // Test Case 7: End blocked
    assert(solve(3, {
        "...",
        "...",
        "..+"
    }) == 0);
    cout << "Test Case 7 Passed" << endl;

    // Test Case 8: All blocked except start/end (impossible if s/e are separate)
    // .+.
    // +++
    // .+.
    assert(solve(3, {
        ".+.",
        "+++",
        ".+."
    }) == 0);
    cout << "Test Case 8 Passed" << endl;
}

int main() {
    test_cases();
    return 0;
}

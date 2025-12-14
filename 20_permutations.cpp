#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ============================================================================
// PROBLEM: Display all n-length permutations of characters in n-length string
// ============================================================================
// Input:  string s of length n
// Output: all n! permutations (print each to stdout, one per line)
//
// Example: s = "ABC" → ABC, ACB, BAC, BCA, CAB, CBA (6 outputs = 3!)
// Example: s = "AB"  → AB, BA (2 outputs = 2!)
// Example: s = "X"   → X (1 output = 1!)
//
// TRAP: s = "AAB" → produces 6 outputs with duplicates, not 3 unique
// ============================================================================

// ----------------------------------------------------------------------------
// TODO: Implement this function
// ----------------------------------------------------------------------------
// perm_helper: recursive backtracking
//
// Parameters:
//   s       - input string (const reference, do not copy)
//   n       - length of s
//   depth   - current recursion depth (0 to n)
//   current - permutation being built
//   used    - used[i] = true if s[i] already in current
//   result  - vector to collect all permutations
//
// Base case: depth == n → push current to result
// Recursive: for each unused index i, pick it, recurse, unpick
// ----------------------------------------------------------------------------
void perm_helper(const string &s, int n, int depth, string &current,
                 vector<bool> &used, vector<string> &result) {
  // TODO: base case
  // depth == n → push current to result, return

  // TODO: recursive case
  // for i = 0 to n-1:
  //     if not used[i]:
  //         used[i] = true
  //         current.push_back(s[i])
  //         recurse with depth+1
  //         current.pop_back()     // ← DO NOT FORGET
  //         used[i] = false        // ← DO NOT FORGET

  if (depth == n) {
    result.push_back(current);
    return;
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      used.at(i) = true;
      current.push_back(s[i]);
      perm_helper(s, n, depth + 1, current, used, result);
      current.pop_back();
      used.at(i) = false;
    }
  }
}

// ----------------------------------------------------------------------------
// permutations: entry point
// ----------------------------------------------------------------------------
// Returns vector of all n! permutations of s
// ----------------------------------------------------------------------------
vector<string> permutations(const string &s) {
  vector<string> result;
  int n = s.size();
  if (n == 0)
    return result;

  string current;
  current.reserve(n); // pre-allocate to avoid reallocation

  vector<bool> used(n, false);

  perm_helper(s, n, 0, current, used, result);

  return result;
}

// ----------------------------------------------------------------------------
// factorial: helper for verification
// ----------------------------------------------------------------------------
long long factorial(int n) {
  long long f = 1;
  for (int i = 2; i <= n; i++) {
    f *= i;
  }
  return f;
}

// ============================================================================
// TEST CASES
// ============================================================================

void test_single_char() {
  // n=1 → 1! = 1 output
  vector<string> result = permutations("X");
  assert(result.size() == 1);
  assert(result[0] == "X");
  cout << "[PASS] test_single_char: n=1, output=1" << endl;
}

void test_two_chars() {
  // n=2 → 2! = 2 outputs
  vector<string> result = permutations("AB");
  assert(result.size() == 2);
  // outputs should be AB, BA (order may vary)
  bool has_AB = false, has_BA = false;
  for (const string &s : result) {
    if (s == "AB")
      has_AB = true;
    if (s == "BA")
      has_BA = true;
  }
  assert(has_AB && has_BA);
  cout << "[PASS] test_two_chars: n=2, output=2" << endl;
}

void test_three_chars() {
  // n=3 → 3! = 6 outputs
  vector<string> result = permutations("ABC");
  assert(result.size() == 6);
  // verify all 6 permutations present
  vector<string> expected = {"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"};
  for (const string &e : expected) {
    bool found = false;
    for (const string &r : result) {
      if (r == e) {
        found = true;
        break;
      }
    }
    assert(found);
  }
  cout << "[PASS] test_three_chars: n=3, output=6" << endl;
}

void test_four_chars() {
  // n=4 → 4! = 24 outputs
  vector<string> result = permutations("1234");
  assert(result.size() == 24);
  // spot check a few
  bool has_1234 = false, has_4321 = false;
  for (const string &s : result) {
    if (s == "1234")
      has_1234 = true;
    if (s == "4321")
      has_4321 = true;
  }
  assert(has_1234 && has_4321);
  cout << "[PASS] test_four_chars: n=4, output=24" << endl;
}

void test_duplicate_chars() {
  // n=3, s="AAB" → 3! = 6 outputs (with duplicates)
  // naive algorithm produces: AAB, ABA, AAB, ABA, BAA, BAA
  vector<string> result = permutations("AAB");
  assert(result.size() == 6); // 3! not 3
  cout << "[PASS] test_duplicate_chars: n=3 with duplicates, output=6" << endl;
}

void test_five_chars() {
  // n=5 → 5! = 120 outputs
  vector<string> result = permutations("ABCDE");
  assert(result.size() == 120);
  cout << "[PASS] test_five_chars: n=5, output=120" << endl;
}

void test_empty() {
  // n=0 → 0 outputs
  vector<string> result = permutations("");
  assert(result.size() == 0);
  cout << "[PASS] test_empty: n=0, output=0" << endl;
}

void test_count_matches_factorial() {
  // verify output count = n! for various n
  for (int n = 1; n <= 6; n++) {
    string s(n, 'A');
    for (int i = 0; i < n; i++)
      s[i] = 'A' + i; // "A", "AB", "ABC", ...
    vector<string> result = permutations(s);
    long long expected = factorial(n);
    assert(result.size() == (size_t)expected);
  }
  cout << "[PASS] test_count_matches_factorial: 1! to 6! verified" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
  cout << "=== Running Permutation Tests ===" << endl;

  test_empty();
  test_single_char();
  test_two_chars();
  test_three_chars();
  test_four_chars();
  test_duplicate_chars();
  test_five_chars();
  test_count_matches_factorial();

  cout << "\n=== All Tests Passed ===" << endl;

  // Print sample output for ABC
  cout << "\n=== Sample Output for s=\"ABC\" ===" << endl;
  vector<string> sample = permutations("ABC");
  for (const string &s : sample) {
    cout << s << endl;
  }

  return 0;
}

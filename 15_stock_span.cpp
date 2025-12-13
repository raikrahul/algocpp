#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

// STACK-BASED SOLUTION with detailed numerical traces in comments
// Problem: compute span S[i] = count of consecutive elements A[j] where A[j] ≤ A[i], including A[i]
// Example: A={6,3,4,5,2} → S={1,1,2,3,1}
// Approach: maintain stack of indices with decreasing values (monotonic stack)
std::vector<int> computeSpanStack(const std::vector<int>& A) {
    int n = A.size();  // n=5 for A={6,3,4,5,2}, represents total elements to process, determines loop bound i<5
    std::vector<int> S(n);  // S={0,0,0,0,0} initially, allocates 5*sizeof(int)=20 bytes on stack/heap, will hold final spans {1,1,2,3,1}
    std::stack<int> stk;  // stk=[] initially, LIFO structure, stores indices not values, top=most recent, bottom=oldest, used to find nearest left element > A[i]
    
    for (int i = 0; i < n; i++) {  // i iterates 0→1→2→3→4, each iteration processes one element, total 5 iterations, i is current position being analyzed
        
        // DISCARD PHASE: pop indices j where A[j] ≤ A[i] because they can never be stoppers for future k>i
        // Why: if A[j] ≤ A[i] and future k scans left, either (1) A[i]>A[k] so i blocks j, or (2) A[i]≤A[k] so A[j]≤A[i]≤A[k] means j not stopper
        // Example i=2, A[2]=4: stk=[0,1] → A[1]=3≤4 → pop 1 → stk=[0] → A[0]=6>4 → stop → stk remains [0]
        // Trace i=2: before=[0,1] → check top=1: A[1]=3, A[2]=4, 3≤4✓ → pop → stk=[0] → check top=0: A[0]=6, 6≤4✗ → exit while
        while (!stk.empty() && A[stk.top()] <= A[i]) {  // stk.empty()=false when size>0, stk.top()=index at top, A[stk.top()]=value at that index
            // i=2 iter₁: stk.empty()=false (size=2), stk.top()=1, A[1]=3, A[2]=4, 3≤4=true → enter body
            // i=3 iter₁: stk.empty()=false (size=2), stk.top()=2, A[2]=4, A[3]=5, 4≤5=true → enter body
            stk.pop();  // removes top element, decrements size by 1, O(1) operation, exposes next element below
            // i=2 after pop: stk=[0,1]→[0], size 2→1, top was 1 now 0
            // i=3 after pop: stk=[0,2]→[0], size 2→1, top was 2 now 0
        }
        // After while at i=2: stk=[0], checked A[0]=6≤4✗ so stopped, 6 is stopper for 4
        // After while at i=3: stk=[0], checked A[0]=6≤5✗ so stopped, 6 is stopper for 5
        
        // SPAN CALCULATION: if stk empty → no stopper → span = i+1 (all left + self), else span = i - stk.top() (distance from stopper)
        // Formula derivation: stopper at j means elements (j+1)..i are ≤ A[i], count = i-(j+1)+1 = i-j, but we want distance so i-j
        // Example i=3, stk=[0]: stopper=0, span=3-0=3, means indices 1,2,3 counted (A[1]=3≤5, A[2]=4≤5, A[3]=5≤5)
        if (stk.empty()) {  // stk.empty()=true when size=0, means all left elements ≤ A[i], no stopper found
            // i=0: stk=[] → empty=true → S[0]=0+1=1 (only self, no left elements)
            S[i] = i + 1;  // i=0→1, i=1 if all≤A[1]→2, counts all indices 0..i inclusive, +1 because i is 0-indexed
            // Calculation: i=0 → 0+1=1 means 1 element (index 0), i=4 if empty → 4+1=5 means all 5 elements
        } else {  // stk not empty, top has index of stopper (first left element > A[i])
            // i=1: stk=[0], top=0, S[1]=1-0=1 (only index 1, stopped by index 0 where A[0]=6>3)
            // i=2: stk=[0], top=0, S[2]=2-0=2 (indices 1,2, stopped by index 0 where A[0]=6>4)
            // i=3: stk=[0], top=0, S[3]=3-0=3 (indices 1,2,3, stopped by index 0 where A[0]=6>5)
            // i=4: stk=[0,3], top=3, S[4]=4-3=1 (only index 4, stopped by index 3 where A[3]=5>2)
            S[i] = i - stk.top();  // distance from stopper to current, stopper not included in count, elements (stopper+1)..i are ≤ A[i]
            // Numerical: i=3, top=0 → 3-0=3 → indices 1,2,3 → values {3,4,5} all ≤5 → count=3 ✓
            // Numerical: i=4, top=3 → 4-3=1 → index 4 only → value {2} ≤2 → count=1 ✓
        }
        
        // ADD CURRENT: push i to stack because it might be stopper for future elements
        // Why: A[i] might be > some future A[k], making i the nearest stopper for k
        // Example: after i=3 (A[3]=5), push 3 → stk=[0,3] → later i=4 (A[4]=2), 5>2 so 3 is stopper
        stk.push(i);  // adds i to top, increments size by 1, O(1) operation
        // i=0: stk=[]→[0], size 0→1
        // i=1: stk=[0]→[0,1], size 1→2
        // i=2: stk=[0]→[0,2], size 1→2 (note: 1 was popped earlier)
        // i=3: stk=[0]→[0,3], size 1→2 (note: 2 was popped earlier)
        // i=4: stk=[0,3]→[0,3,4], size 2→3
    }
    
    return S;  // S={1,1,2,3,1} for A={6,3,4,5,2}, each S[i] is span at position i
}

// ORIGINAL JUMP-BASED SOLUTION (kept for comparison)
std::vector<int> computeSpan(const std::vector<int>& A) {
    int n = A.size();
    std::vector<int> S(n);
    
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && A[j] <= A[i]) {
            j = j - S[j];
        }
        if (j < 0) {
            S[i] = i + 1;
        } else {
            S[i] = i - j;
        }
    }
    return S;
}

void test_example() {
    std::vector<int> A = {6, 3, 4, 5, 2};
    std::vector<int> expected = {1, 1, 2, 3, 1};
    std::vector<int> result = computeSpanStack(A);
    assert(result == expected);
    std::cout << "test_example passed" << std::endl;
}

void test_ascending() {
    std::vector<int> A = {1, 2, 3, 4};
    std::vector<int> expected = {1, 2, 3, 4};
    std::vector<int> result = computeSpanStack(A);
    assert(result == expected);
    std::cout << "test_ascending passed" << std::endl;
}

void test_descending() {
    std::vector<int> A = {4, 3, 2, 1};
    std::vector<int> expected = {1, 1, 1, 1};
    std::vector<int> result = computeSpanStack(A);
    assert(result == expected);
    std::cout << "test_descending passed" << std::endl;
}

void test_plateau() {
    std::vector<int> A = {5, 5, 5, 5};
    std::vector<int> expected = {1, 2, 3, 4};
    std::vector<int> result = computeSpanStack(A);
    assert(result == expected);
    std::cout << "test_plateau passed" << std::endl;
}

void test_single() {
    std::vector<int> A = {7};
    std::vector<int> expected = {1};
    std::vector<int> result = computeSpanStack(A);
    assert(result == expected);
    std::cout << "test_single passed" << std::endl;
}

void test_peak() {
    std::vector<int> A = {1, 2, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 1, 1};
    std::vector<int> result = computeSpanStack(A);
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

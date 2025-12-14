# Subset Sum Combinations

**Problem**: Given sorted array, find all combinations summing to S. Also handle unsorted case.

---

## Input→Output Examples

```
arr=[1,2,3,4,5], S=7 → {1,2,4}, {2,5}, {3,4}, {1,2,4} ✗ wait {1,2,4}=7 ✓, {2,5}=7 ✓, {3,4}=7 ✓
arr=[2,3,5], S=8 → {3,5}=8 ✓
arr=[1,1,2,3], S=4 → {1,1,2}=4 ✓, {1,3}=4 ✓ (multiple 1s create duplicate issue)
arr=[], S=5 → {} (empty array → 0 combinations)
arr=[7], S=7 → {7} ✓
arr=[8], S=7 → {} (single element > S → 0 combinations)
arr=[1,2,3], S=100 → {} (sum of all = 6 < 100 → 0 combinations)
```

---

## Step-by-Step Derivation

01. Draw array arr=[1,2,3,4,5] at memory 0x100: |1|2|3|4|5|, indices {0,1,2,3,4}, n=5, S=7, total subsets = 2^5 = 32, you must enumerate all 32 subsets by binary representation 00000 to 11111, subset 00000 = {} sum=0≠7 ✗, subset 00001 = {5} sum=5≠7 ✗, subset 00010 = {4} sum=4≠7 ✗, subset 00011 = {4,5} sum=9>7 ✗, subset 00100 = {3} sum=3≠7 ✗, continue this for all 32 → brute force O(2^n) time.

02. Count subsets for n=5: 2^5=32, for n=10: 2^10=1024, for n=20: 2^20=1048576, for n=30: 2^30=1073741824≈10^9 → brute force fails at n≥25, you will skip this calculation and assume brute force works → F1: timeout on large n.

03. arr=[1,2,3] at 0x100: |1|2|3|, idx={0,1,2}, n=3, S=4, total subsets=2^3=8, enumerate all 8:
```
subset_0 = binary 000 = pick nothing     = {}      → sum=0   → 0≠4 ✗
subset_1 = binary 001 = pick idx2        = {3}     → sum=3   → 3≠4 ✗
subset_2 = binary 010 = pick idx1        = {2}     → sum=2   → 2≠4 ✗
subset_3 = binary 011 = pick idx1,idx2   = {2,3}   → sum=5   → 5≠4 ✗
subset_4 = binary 100 = pick idx0        = {1}     → sum=1   → 1≠4 ✗
subset_5 = binary 101 = pick idx0,idx2   = {1,3}   → sum=4   → 4=4 ✓ OUTPUT
subset_6 = binary 110 = pick idx0,idx1   = {1,2}   → sum=3   → 3≠4 ✗
subset_7 = binary 111 = pick idx0,idx1,idx2={1,2,3}→ sum=6   → 6≠4 ✗
```
result: 1 valid subset {1,3}, pruning definition: at idx=i with running sum=s, if s+arr[i]>S AND array sorted, then s+arr[i+1]≥s+arr[i]>S, so skip idx=i and all j>i, example: at idx=0 sum=0, 0+1=1≤4 so cannot prune, at idx=1 sum=1, 1+2=3≤4 cannot prune, at idx=2 sum=3, 3+3=6>4 ∴ prune=skip idx=2, but wait arr=[1,2,3] is sorted so if 3+3=6>4 then no more elements to check anyway since idx=2 is last, better example for pruning: arr=[1,2,5,6], S=4, at idx=0 sum=0: 0+1=1≤4 pick, at idx=1 sum=1: 1+2=3≤4 pick, at idx=2 sum=3: 3+5=8>4 ∴ PRUNE here, do not check idx=3 because arr[3]=6≥5 so sum+6≥8>4 guaranteed, this saves 2^(n-3)=2^1=2 subsets from enumeration.

04. arr=[1,2,3,4,5], S=7, sorted=✓, start idx=0 sum=0: pick 1 → sum=1, pick 2 → sum=3, pick 3 → sum=6, pick 4 → sum=10>7 ✗ prune this branch, backtrack to sum=6, skip 4 pick 5 → sum=11>7 ✗ prune, backtrack to sum=3, skip 3 pick 4 → sum=7=S ✓ output [1,2,4], this is backtracking with pruning, sorted array enables early termination when sum>S because all remaining elements ≥ current element.

05. Pruning condition for sorted array: at index i with current sum, if sum + arr[i] > S → skip arr[i] and all elements after, because arr[j] ≥ arr[i] for j>i → sum + arr[j] > S guaranteed, you will forget this condition and check all elements → F2: missing early termination, time complexity degrades from O(2^k) where k<n to O(2^n).

06. Draw backtracking state for arr=[2,3,5], S=8: call(0,0,[]) → loop i=0: sum+2=2≤8, push 2, call(1,2,[2]) → loop i=1: sum+3=5≤8, push 3, call(2,5,[2,3]) → loop i=2: sum+5=10>8 ✗ return, pop 3, i=2: sum+5=7≤8, push 5, call(3,7,[2,5]) → i=3 out of bounds, 7≠8 return, pop 5, return to (1,2,[2]) → pop 2, i=1: sum+3=3≤8, push 3, call(2,3,[3]) → i=2: sum+5=8=S ✓ output [3,5], this trace shows start index must be i+1 not 0 to avoid reusing elements.

07. Duplicate elements arr=[1,1,2,3], S=4: indices {0,1,2,3}, arr[0]=1 arr[1]=1, if you pick arr[0] then pick arr[2] → [1,2] sum=3, then pick arr[3] → [1,2,3] sum=6>4 ✗, backtrack, skip arr[3], check arr[1] already processed? → you will generate [1,3] from idx=0 AND [1,3] from idx=1 → duplicate outputs, F3: not skipping duplicate values at same recursion level, fix: if i>start && arr[i]==arr[i-1] skip.

08. Draw skip logic for arr=[1,1,2,3], S=4 sorted: call(0,0,[],start=0) → i=0: push 1, call(1,1,[1],start=1) → i=1: arr[1]=1, i>start? 1>1 ✗ so process, push 1, call(2,2,[1,1],start=2) → i=2: push 2, sum=4=S ✓ output [1,1,2], pop 2, i=3: push 3, sum=5>4 ✗ pop 3 return, pop 1, i=2: push 2, call(3,3,[1,2],start=3) → i=3: push 3, sum=6>4 ✗, pop return, pop 2, i=3: push 3, sum=4=S ✓ output [1,3], back to level 0 → i=1: arr[1]=1=arr[0] AND i>start (1>0) ✓ skip! this prevents duplicate [1,3].

09. Unsorted array arr=[3,1,4,2], S=5: cannot use early termination because arr[i+1] might be < arr[i], must sort first or enumerate all 2^4=16 subsets, sorting cost O(n log n), total O(n log n + 2^k), you will skip sorting and apply sorted pruning → F4: incorrect pruning on unsorted array, subset {1,4}=5 ✓ might be missed if you prune at 3+1=4<5 but then stop at 4>5 without checking 2.

10. Edge case arr=[], S=0: empty subset {} sums to 0, is {} a valid combination? problem says "combinations of given array elements" → {} uses 0 elements, you must clarify: S=0 with empty array → output {} or output nothing? if S=0 with arr=[1,2,3] → {} is only combination with sum=0, F5: unclear specification for S=0 case.

11. Edge case arr=[5,5,5], S=10: sorted, call(0,0,[],start=0) → i=0: push 5, call(1,5,[5],start=1) → i=1: push 5, sum=10=S ✓ output [5,5], pop 5, i=2: arr[2]=5=arr[1] AND i>start (2>1) ✓ skip, return, pop 5, i=1: arr[1]=5=arr[0] AND i>start (1>0) ✓ skip, i=2: skip similarly, result: only one [5,5] output, but wait: skip at i=1 means we never try starting with arr[1], this is correct because arr[0]=arr[1]=5 → combinations starting with either are equivalent.

12. Complexity analysis: worst case all subsets valid, 2^n subsets, each subset takes O(n) to copy → O(n×2^n) time, space for recursion stack O(n), space for storing results O(n×2^n), you will forget output space and claim O(n) space → F6: ignoring output storage.

13. Draw function signature: void findCombinations(vector<int>& arr, int target, int start, int currentSum, vector<int>& current, vector<vector<int>>& result), parameters: arr=input, target=S, start=next index to consider, currentSum=running sum, current=current combination being built, result=all valid combinations, you will confuse start with currentSum → F7: parameter mixup.

14. For unsorted solve: option A = sort then apply sorted algorithm O(n log n + 2^k), option B = use hashmap approach for two-sum variant only (not general subset sum), option C = brute force all 2^n subsets O(2^n), for combinations (not just existence), sorting is optimal because it enables pruning AND deduplication via skip condition.

15. Negative numbers arr=[-1,1,2,3], S=3: sum=-1+1+2+3=5, combinations: {3}=3 ✓, {1,2}=3 ✓, {-1,1,3}=3 ✓, {-1,1,2} wait -1+1+2=2≠3, negative numbers break early termination: if sum + arr[i] > S, cannot prune because later negative might reduce sum, you will apply sorted pruning blindly → F8: pruning fails with negatives.

---

## Failure Predictions

- F1: Brute force timeout at n≥25, 2^25=33554432 operations
- F2: Missing sorted array early termination, checking all elements unnecessarily
- F3: Generating duplicate combinations when array has repeated values
- F4: Applying sorted pruning to unsorted array
- F5: Unclear handling of S=0 edge case
- F6: Claiming O(n) space, forgetting output storage O(n×2^n)
- F7: Confusing start index with current sum in recursion parameters
- F8: Early termination invalid when negatives present
- F9: Using i=0 instead of i=start in loop → reusing elements → invalid combinations
- F10: Forgetting to pop from current vector after recursion → current grows unbounded
- F11: Base case sum==target not returning immediately → continuing to add more elements
- F12: Modifying input array (sorting) when caller expects unchanged array

---

## Data Structure Trace

```
arr = [1,2,3,4,5], S=7

Memory layout at 0x100:
+-----+-----+-----+-----+-----+
|  1  |  2  |  3  |  4  |  5  |
+-----+-----+-----+-----+-----+
0x100 0x104 0x108 0x10C 0x110
idx=0 idx=1 idx=2 idx=3 idx=4

Recursion call stack (partial trace):

call_0: start=0, sum=0, curr=[]
  ├─ i=0: sum+1=1≤7, push(1), call_1
  │   call_1: start=1, sum=1, curr=[1]
  │   ├─ i=1: sum+2=3≤7, push(2), call_2
  │   │   call_2: start=2, sum=3, curr=[1,2]
  │   │   ├─ i=2: sum+3=6≤7, push(3), call_3
  │   │   │   call_3: start=3, sum=6, curr=[1,2,3]
  │   │   │   ├─ i=3: sum+4=10>7 ✗ prune
  │   │   │   └─ i=4: sum+5=11>7 ✗ prune
  │   │   │   return (no output, 6≠7)
  │   │   │   pop(3), curr=[1,2]
  │   │   ├─ i=3: sum+4=7=S ✓ OUTPUT [1,2,4]
  │   │   │   call_3: start=4, sum=7, curr=[1,2,4]
  │   │   │   7=7 but continue? no, i=4: sum+5=12>7 prune
  │   │   │   pop(4), curr=[1,2]
  │   │   ├─ i=4: sum+5=8>7 ✗ prune
  │   │   pop(2), curr=[1]
  │   ├─ i=2: sum+3=4≤7, push(3), ...
  │   ...continues...

Final outputs: [1,2,4], [2,5], [3,4]
Verify: 1+2+4=7 ✓, 2+5=7 ✓, 3+4=7 ✓
```

---

## Calculations To Perform By Hand

Calculate 01: 2^n for n={5,10,15,20,25,30} → {32, 1024, 32768, 1048576, 33554432, 1073741824}, this shows growth rate, at n=20 you hit 10^6 operations, at n=30 you hit 10^9 → timeout threshold.

Calculate 02: For arr=[1,2,3,4,5,6,7,8,9,10], S=15, how many subsets sum to exactly 15? Enumerate: {1,2,3,4,5}=15 ✓, {1,2,3,9}=15 ✓, {1,2,4,8}=15 ✓, {1,2,5,7}=15 ✓, {1,2,6,7} wait 1+2+6=9+7=16≠15, {1,3,4,7}=15 ✓, {1,3,5,6}=15 ✓, {1,4,10}=15 ✓, {1,5,9}=15 ✓, {1,6,8}=15 ✓, {2,3,4,6}=15 ✓, {2,3,10}=15 ✓, {2,4,9}=15 ✓, {2,5,8}=15 ✓, {2,6,7}=15 ✓, {3,4,8}=15 ✓, {3,5,7}=15 ✓, {4,5,6}=15 ✓, {5,10}=15 ✓, {6,9}=15 ✓, {7,8}=15 ✓ → count these by hand.

Calculate 03: arr=[1,1,1,1], S=2, without duplicate handling: how many times does [1,1] appear? C(4,2)=6 ways to choose 2 ones, but all produce same [1,1] → 6 duplicates, with duplicate handling: skip when arr[i]==arr[i-1] and i>start → only 1 output.

Calculate 04: For sorted arr=[1,2,4,8,16], S=31, optimal path: 1+2+4+8+16=31 ✓, only one combination, but algorithm will explore many dead ends: path [1,2,4,8] sum=15<31, must add 16→31 ✓, path [1,2,4,16] sum=23<31, need 8 more but 8 already passed, backtrack, count total recursion calls vs actual valid combinations.

Calculate 05: Space for result storage: if n=20 and on average 10% of subsets are valid → 0.1 × 2^20 = 104857 combinations, each combination averages n/2=10 elements, total storage = 104857 × 10 × 4 bytes = 4194280 bytes ≈ 4MB.

Calculate 06: arr=[2,4,6,8,10], S=7, odd target with all even elements → sum of any subset = even, 7=odd → 0 combinations possible, you can check this in O(1) upfront: if all elements and S have different parity → return immediately.

Calculate 07: arr=[1,2,3,...,n], S=n(n+1)/2 (sum of all), only one combination = entire array, but algorithm explores 2^n paths, worst case inefficiency when only full set works.

---

## Implementation Mistakes

M1. line 47 → `arr.max_size()` → returns ~10^18 → out-of-bounds crash → fix: `arr.size()` → missed: did not check return type of max_size vs size → prevent: always use `size()` for bounds

M2. line 51-53 → `result.push_back(current)` before `current.push_back(arr[i])` → saves incomplete subset [1] instead of [1,3] → fix: push element first, then save → missed: order of operations → prevent: trace with real data before writing

M3. line 47-61 → no duplicate skip check → arr=[1,1,2,3] produces [1,3] twice → fix: add `if (i > start && arr[i] == arr[i-1]) continue` → missed: duplicate values at same recursion level → prevent: always ask "what if arr has duplicates?"

M4. line 55 → `i > start` check → asked "why check i>start, always true" → wrong: i=start on first iteration → prevent: trace loop from i=start not i=0

M5. confusion → "why pop_back when sum==target, we found answer" → wrong: other subsets may exist → missed: search continues after finding one answer → prevent: enumerate small example to see multiple answers

M6. confusion → "why push/pop in both if and else" → wrong: continue skips else block → missed: control flow with continue → prevent: trace which lines execute for each branch

M7. confusion → "why for loop" → wrong: assumed recursion alone handles all branches → missed: loop tries each i as starting pick → prevent: draw decision tree

M8. confusion → "permutations use i=0, subsets use i=start" → root cause: unclear on ordering → subsets unordered (skip previous), permutations ordered (can reuse any unused) → prevent: distinguish "order matters" vs "order irrelevant"

M9. confusion → "prune check inside vs outside loop" → wrong: assumed same as permutation base case → prune depends on arr[i] (loop variable), base case depends on depth (recursion parameter) → prevent: ask "does condition depend on i or on recursion level?"

M10. line 55 → type warning → `size_t i` compared with `int start` → fix: cast or use consistent types → low priority but indicates sloppy type handling

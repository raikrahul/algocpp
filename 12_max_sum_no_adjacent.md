
[ DATA_STRUCTURE: Input_Array_01 ]
| Index | 00 | 01 | 02 | 03 |
| Value | 03 | 02 | 07 | 10 |
+-------+----+----+----+----+
      ↓
01. Definition: Subset S ⊆ Input : ∀ a,b ∈ S, |index(a) - index(b)| > 1.
02. Goal: Maximize ∑(value(x) for x ∈ S).
03. Enumeration_01: List all 2⁴=16 subsets.
04. Filter_Validity_01: {3,2}→idx{0,1}→diff=1→✗. {2,7}→idx{1,2}→diff=1→✗. {7,10}→idx{2,3}→diff=1→✗.
05. Filter_Validity_02: {3,7}→idx{0,2}→diff=2→✓. {3,10}→idx{0,3}→diff=3→✓. {2,10}→idx{1,3}→diff=2→✓.
06. Filter_Validity_03: {3,2,7}→contains {3,2}→✗. {3,7,10}→contains {7,10}→✗.
07. Calculate_Sums_Valid: {3}=3, {2}=2, {7}=7, {10}=10. {3,7}=10. {3,10}=13. {2,10}=12.
08. Compare_Sums: 3, 2, 7, 10, 10, 13, 12.
09. Max_Value: 13.
10. Winning_Subset: {3, 10}.
11. Conclusion_01: You must derive this purely by numbers. No guessing.

[ DATA_STRUCTURE: Failure_Case_Greedy ]
| Index | 00 | 01 | 02 |
| Value | 10 | 20 | 15 |
+-------+----+----+----+
      ↓
12. Strategy_Greedy: "Always pick the largest number available".
13. Step_01: Max is 20 (at index 01). Pick {20}.
14. Constraint_Check: Index 01 picked → Neighbors 00, 02 blocked.
15. Remaining_Available: None.
16. Greedy_Result: Sum = 20.
17. Manual_Check: Option A {10} + Option C {15} (Indices 00, 02).
18. Validity: |00-02| = 2 > 1 ✓.
19. Sum_Alternative: 10 + 15 = 25.
20. Comparison: 25 > 20 ∴ Greedy Strategy ✗.
21. Root_Cause: Picking local max (20) destroyed opportunity to pick two satisfactory neighbors (10+15).
22. Inference: Decision at `i` depends on future/global context, or need to explore both "Keep" and "Discard" paths.

[ DATA_STRUCTURE: Failure_Case_Parity ]
| Index | 00 | 01 | 02 | 03 | 04 | 05 |
| Value | 05 | 05 | 10 | 40 | 50 | 35 |
+-------+----+----+----+----+----+----+
      ↓
23. Strategy_Parity: "Sum all even indices vs Sum all odd indices".
24. Sum_Evens: idx{0,2,4} → 5 + 10 + 50 = 65.
25. Sum_Odds: idx{1,3,5} → 5 + 40 + 35 = 80.
26. Max_Parity: 80.
27. Manual_Optimum_Search: Try mixed parity?
28. Mixed_Set: {5 (idx0), 40 (idx3), 35 (idx5)} ?
29. Checks: |0-3|=3✓. |3-5|=2✓.
30. Sum_Mixed: 5 + 40 + 35 = 80. Same?
31. Wait_Try_Another: {5 (idx1), 50 (idx4)}? |1-4|=3✓. Sum=55.
32. Wait_Try_Another: {5 (idx0), 10 (idx2)? No adj? No |0-2|=2✓. {5, 10, 50, ... No idx 4 adj 2? No |2-4|=2✓.
33. Try: {5(0), 10(2), 50(4)} = 65.
34. The Parity strategy yields 80 correctly here?
35. Counter_Example_Parity: {5, 1, 1, 5}.
36. Evens: 5(0)+1(2)=6. Odds: 1(1)+5(3)=6.
37. Optimum: 5(0)+5(3)? Gap |0-3|=3✓. Sum=10.
38. Result: 10 > 6 ∴ Parity Strategy ✗.
39. Inference: Optimal solution can mix odd/even indices arbitrarily as long as gap > 1.

[ DATA_STRUCTURE: Recurrence_Trace_Machine ]
Input: {3, 2, 7, 10}
Addr_Space: [Stack Frames]
      ↓
40. Comput_f(3, val=10): Choice A: Pick 10 + f(1). Choice B: Skip 10 + f(2).
41. Comput_f(2, val=07): Choice A: Pick 07 + f(0). Choice B: Skip 07 + f(1).
42. Comput_f(1, val=02): Choice A: Pick 02 + f(-1)→0. → Sum=2. Choice B: Skip 02 + f(0).
43. Comput_f(0, val=03): Choice A: Pick 03 + 0 = 3. Choice B: Skip 03 + 0 = 0. → Max=3.
44. Backprop_f(1): Pick(2+0) vs Skip(3) → Max(2,3) = 3.
45. Backprop_f(2): Pick(7+3)=10 vs Skip(3) → Max(10,3) = 10.
46. Backprop_f(3): Pick(10+3)=13 vs Skip(10) → Max(13,10) = 13.
47. Result: 13 ✓.Matches Step 09.
48. Formula_Derivation: f(i) = Max( nums[i] + f(i-2), f(i-1) ).

[ DATA_STRUCTURE: Memory_Layout_Linear ]
Variables: `prev2`, `prev1`, `curr`
Initial: `prev2`=0, `prev1`=nums[0]
      ↓
49. Worksheet_Task: Execute algorithm by hand for {5, 5, 10, 100, 10, 5}.
50. Init: prev2=0, prev1=5 (the first 5).
51. Iteration i=1 (Val=5):
    - Option_Pick: 5 + prev2(0) = 5.
    - Option_Skip: prev1(5).
    - curr = Max(5, 5) = 5.
    - Shift: prev2 ← 5, prev1 ← 5.
52. Iteration i=2 (Val=10):
    - Option_Pick: 10 + prev2(5) = 15.
    - Option_Skip: prev1(5).
    - curr = Max(15, 5) = 15.
    - Shift: prev2 ← 5, prev1 ← 15.
53. Iteration i=3 (Val=100):
    - Option_Pick: 100 + prev2(5) = 105.
    - Option_Skip: prev1(15).
    - curr = Max(105, 15) = 105.
    - Shift: prev2 ← 15, prev1 ← 105.
54. Iteration i=4 (Val=10):
    - Option_Pick: 10 + prev2(15) = 25.
    - Option_Skip: prev1(105).
    - curr = Max(25, 105) = 105.
    - Shift: prev2 ← 105, prev1 ← 105.
55. Iteration i=5 (Val=5):
    - Option_Pick: 5 + prev2(105) = 110.
    - Option_Skip: prev1(105).
    - curr = Max(110, 105) = 110.
    - Shift: prev2 ← 105, prev1 ← 110.
56. Final_Result: 110.
57. Check: 5(idx0) + 100(idx3) + 5(idx5) = 110.
58. Indices: 0, 3, 5.
59. Gaps: 3-0=3>1✓. 5-3=2>1✓.
60. ∴ Calculation Correct.

[ EXERCISE_BLOCK: Do It Yourself ]
61. Calculate_01: Input = {1, 2, 3}. Trace prev2, prev1.
62. Calculate_02: Input = {9, 9, 8, 2}. Trace prev2, prev1.
63. Calculate_03: Input = {5, 1, 1, 5}. Trace prev2, prev1. Confirm Result=10.
64. Complexity_Analysis:
    - Time: One pass loop → N steps → O(N).
    - Space: Variables prev2, prev1, curr → O(1).
    - Integers: Sum can exceed 2³¹? n=10⁵, max_val=10⁹ → Sum≈10¹⁴ > 2³¹ ∴ Use `long long`.

[ ERROR_REPORT: Mistakes During Derivation ]

E01. Confusion: "Skip element → sum stays at 3".
     Wrong: Skip idx3(10) in {3,2,7,10} → thought sum=3.
     Correct: Skip idx3 → use f(2)=10 (not f(0)=3).
     Root: Confused f(i-1) with f(i-2). Did not trace dependency chain.
     Prevention: Draw memory state [0x100]=f(0), [0x104]=f(1), [0x108]=f(2) before each step.

E02. Confusion: "Include element always increases sum".
     Wrong: Assumed more elements = larger sum.
     Correct: Include blocks neighbor → may lose larger neighbor value.
     Example: {1,100,1} → Include 1(idx2) → lose 100 → sum=2. Exclude 1(idx2) → keep 100 → sum=100.
     Root: Ignored constraint "no adjacent".
     Prevention: Brute force enumerate all valid subsets before optimizing.

E03. Confusion: "Why need temp variable best_here?"
     Wrong: Tried best_1_back = max(...); best_2_back = best_1_back;
     Correct: best_here = max(...); best_2_back = old_best_1_back; best_1_back = best_here;
     Root: Overwrote best_1_back before using its old value.
     Prevention: Trace with numbers: best_1_back=5 → overwrite to 15 → best_2_back gets 15 (wrong, should be 5).

E04. Confusion: "What do prev2 and prev1 mean?"
     Wrong: No clear mental model.
     Correct: prev2 = best sum for indices 0..(i-2). prev1 = best sum for indices 0..(i-1).
     Root: Named variables without understanding.
     Prevention: Rename to best_2_back, best_1_back. Trace what each holds at every iteration.

E05. Confusion: "Loop starts at i=0 or i=1?"
     Wrong: Uncertain about initialization.
     Correct: Init prev1=nums[0] handles i=0. Loop starts i=1.
     Root: Did not trace base case setup.
     Prevention: Write init → draw state → confirm covers i=0 → loop from i=1.

[ COMPLETED ]
Tests: 10/10 PASS.
Time: O(n).
Space: O(1).

10. tips = [1, 10] → n=2, slots t=0, t=1.
11. Order A: i=0 (val 1) @ t=0, i=1 (val 10) @ t=1 → (1-0) + (10-1) = 1 + 9 = 10.
12. Order B: i=1 (val 10) @ t=0, i=0 (val 1) @ t=1 → (10-0) + (1-1) = 10 + 0 = 10.
13. Order A == Order B. ✓ (Both > t).
14. tips = [0, 10] → n=2.
15. Order A: 0 @ t=0, 10 @ t=1 → (0-0) + (10-1) = 0 + 9 = 9.
16. Order B: 10 @ t=0, 0 @ t=1 → (10-0) + (0-1) → 10 + max(0, -1) = 10 + 0 = 10.
17. 10 > 9 ∴ Order B (Desc) > Order A (Asc). ✓
18. tips = [5, 4, 3] → n=3.
19. Desc: 5 @ 0, 4 @ 1, 3 @ 2 → 5 + 3 + 1 = 9.
20. Asc: 3 @ 0, 4 @ 1, 5 @ 2 → 3 + 3 + 3 = 9.
21. tips = [100, 1] → Desc: 100+0=100. Asc: 1+99=100.
22. tips = [100, 0] → Desc: 100+0=100. Asc: 0+99=99. ∴ Desc > Asc.
23. Hypothesis: Sort Descending maximizes sum.
24. Data: [1, 7, 3, 4]. Sorted: [7, 4, 3, 1].
25. Calc: 7@0 + 4@1 + 3@2 + 1@3 = 7 + 3 + 1 + 0 = 11.
26. Alt Order: [1, 3, 4, 7]. 1@0 + 3@1 + 4@2 + 7@3 = 1 + 2 + 2 + 4 = 9.
27. 11 > 9. ✓
28. Fail check: tips = [ ] → n=0 → sum=0.
29. Fail check: tips = [5] → 5-0 = 5.
30. Int Overflow? sum can be approx n * max_tip. n=10^5, tip=10^5 → 10^10 > 2^31. ∴ return long long.
31. Time Cplx: Sort = O(N log N). Loop = O(N). Tot = O(N log N).
32. Space Cplx: Sort in-place = O(1) or O(log N).
33. tips[i] - t < 0 → add 0.
34. Logic: for i in 0..n-1: sum += max(0, tips[i] - i).
35. vector<int> or array? Proto says int tips[], int n. ∴ use std::sort(tips, tips+n, greater<int>()).
36. Trace: tips=[2, 2, 2]. Sorted [2, 2, 2].
37. i=0: 2-0=2. i=1: 2-1=1. i=2: 2-2=0. Sum=3.
38. Trace: tips=[1, 2, 3]. Sorted [3, 2, 1].
39. i=0: 3-0=3. i=1: 2-1=1. i=2: 1-2=0 (val is 1, t=2, 1-2=-1→0). Sum=4.
40. Final Algo: 1. Sort Desc. 2. Accumulate max(0, val-idx). 3. Ret sum.

## Failure Log

### Mistake 1: Logical Formula Mismatch
- **Code:** `i * tips[i]`
- **Should Be:** `tips[i] - i`
- **Correction Trace:**
  - Input: `Tips=[10]`, `t=0`.
  - Wrong: `0 * 10 = 0`. (Bankrupt).
  - Right: `10 - 0 = 10`. (Profit).
- **Why:** Associating "time" with "multiplication" instead of "subtraction/decay".
- **Prevent:** Run $t=0$ trace manually before typing.

### Mistake 2: Syntax Structure
- **Code:** Unclosed `{` inside loop.
- **Result:** Compilation Error `expected '}'`.
- **Why:** Sloppy coding, rushing to type logic.
- **Prevent:** Type closing brace immediately after opening brace.

### Mistake 3: Arithmetic Failure
- **Calc:** `100 + 49 + 0` calculated as `148`.
- **Should Be:** `149`.
- **Why:** Mental arithmetic drift.
- **Prevent:** Write intermediate sums: $100+40=140$, $9+0=9$, $140+9=149$.

### Mistake 4: Logic Drift
- **Thought:** Ascending order logic not verified.
- **Reality:** Failed to see `Zero Floor` prevents loss for small numbers.
- **Why:** Intuition override ("Order doesn't matter").
- **Prevent:** Prove with extreme values (`1` vs `100`) axiomatically.

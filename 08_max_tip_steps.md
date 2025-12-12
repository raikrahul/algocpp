1. Define inputs: T=[1, 10, 5], N=3. Draw array T with indices 0, 1, 2. Write slots t=0, t=1, t=2.
2. Calculate Permutation P1: [1, 10, 5]. Map to times: 1@0, 10@1, 5@2.
3. Calc Cost P1: (1-0) + (10-1) + (5-2) = 1 + 9 + 3 = 13. Write "13".
4. Calculate Permutation P2: [10, 5, 1]. Map: 10@0, 5@1, 1@2.
5. Calc Cost P2: (10-0) + (5-1) + (1-2) → 10 + 4 + max(0, -1) = 14 + 0 = 14. Write "14".
6. Compare: 14 > 13. ∴ P2 > P1.
7. Observe properties of P2: 10 > 5 > 1. Sorted Descending.
8. Define inputs: T=[3, 4], N=2.
9. Calc P1 (Asc): [3, 4] → 3@0 + 4@1 = 3 + 3 = 6.
10. Calc P2 (Desc): [4, 3] → 4@0 + 3@1 = 4 + 2 = 6.
11. Observe: 6 == 6. Why? (4-3) = (1-0). Difference is 1. One loses 1, other gains 1? No.
12. Analyze Difference: Swap A, B where A at t, B at t+1.
13. Case 1: Order A, B. Val = (A-t) + (B-(t+1)) = A + B - 2t - 1.
14. Case 2: Order B, A. Val = (B-t) + (A-(t+1)) = A + B - 2t - 1.
15. Result: If A, B both > t+1, order doesn't matter? Wait. Check step 1.
16. Re-calc Step 9: 3@0=3, 4@1=3. Sum=6. Step 10: 4@0=4, 3@1=2. Sum=6.
17. Check Data: T=[5, 100]. Asc: 5@0=5, 100@1=99. Sum=104. Desc: 100@0=100, 5@1=4. Sum=104.
18. Check Data: T=[1, 100]. Asc: 1+99=100. Desc: 100+0=100.
19. Does order NEVER matter? ✗. See Step 4-6. [1, 10, 5].
20. Re-calc P1 [1, 10, 5]: 1@0=1. 10@1=9. 5@2=3. Sum=13.
21. Re-calc P2 [10, 5, 1]: 10@0=10. 5@1=4. 1@2=0(neg). Sum=14.
22. Difference source: The truncation `max(0, val-t)`.
23. If `val - t` stays positive, sum is constant.
24. If `val - t` hits 0, we lose value.
25. To maximize sum, we must avoid hitting 0 for large numbers.
26. Large numbers have more "runway" before hitting 0, but they contribute MOST to the sum.
27. Small numbers hit 0 faster.
28. If we put Small S late, it hits 0. We get 0.
29. If we put Large L late, it might not hit 0. We get L - t.
30. Compare S@early + L@late vs L@early + S@late.
31. P1: S@0 + L@1 = S + (L-1). (Assuming L-1 > 0).
32. P2: L@0 + S@1 = L + (S-1). (Assuming S-1 > 0).
33. Result: S+L-1 vs L+S-1. Equal.
34. P1: S@0 + L@late (where S would die). S + (L - late).
35. P2: L@0 + S@late (where S dies). L + 0.
36. Compare S + L - late vs L.
37. Cancel L: S - late vs 0.
38. Since S is placed late, implies we are at time `late`. If `S < late`, then `S - late` is negative.
39. But formula is max(0).
40. Let's trace T=[2], t=5. 2-5 = -3 → 0.
41. Back to Step 36.
42. Scenario: T=[2, 10], N=2. Time slots 8, 9 (Shifted problem).
43. A: 2@8, 10@9. 2-8 < 0 → 0. 10-9 = 1. Sum = 1.
44. B: 10@8, 2@9. 10-8 = 2. 2-9 < 0 → 0. Sum = 2.
45. 2 > 1 ∴ Order B (Desc) wins.
46. General Principle: Sort Descending ensures largest values get earliest slots to stay positive longest? No, actually largest values can survive delays better?
47. Wait. In Step 44, 10 (Large) went FIRST. 2 (Small) went LAST.
48. If 10 went last (Step 43), it survived (value 1). 2 went first, it died (value 0).
49. So Descending Order put Large first.
50. Why? Because Large @ First gives max immediate value.
51. But Large @ Last survives better?
52. Let's re-eval Step 43/44.
53. 2@8 means 2 is served at t=8.
54. (2-8) is neg. (10-9) is 1.
55. (10-8) is 2. (2-9) is neg.
56. Total A = 1. Total B = 2.
57. By putting 10 early, we got 2. By putting 10 late, we got 1. 2 > 1.
58. We lose 1 per second.
59. 10 loses 1 unit of value per second.
60. 2 loses 1 unit of value per second.
61. But 2 hits floor 0 at t=2. 10 hits floor 0 at t=10.
62. Once at 0, you stop losing value (you stay at 0).
63. So "loss rate" is 1 if val > t, else 0.
64. To maximize sum, we want to maximize the time we are "losing" value? No.
65. We want to capture distinct values before they vanish.
66. Sort Descending is the Strategy.
67. Coding Task: Create `main` with `vector<int> tips = { ... }`.
68. Call `sort(rbegin, rend)`.
69. Loop `i` from 0 to N. `sum += max(0, tips[i] - i)`.
70. Print sum.
71. Verify with manual calculation [1, 10, 5, 2]. Sorted: 10, 5, 2, 1.
72. 10@0=10. 5@1=4. 2@2=0. 1@3=0. Sum=14.
73. Verify [1, 10, 5, 2] Anti-Sort: 1, 2, 5, 10.
74. 1@0=1. 2@1=1. 5@2=3. 10@3=7. Sum=12.
75. 14 > 12. ✓

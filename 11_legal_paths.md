1. Grid = 2D array, n×n square, entries ∈ {'.', '+'}, '.' = can step here, '+' = cannot step here.
2. Position = (row, col), 0-indexed in code, problem says (1,1) = top-left = (0,0) in code, (n,n) = bottom-right = (n-1,n-1) in code.
3. Legal path = sequence of positions from Start to End, each move = Right (+1 to col) OR Down (+1 to row), never step on '+'.
4. Right = same row, col increases by 1: (r,c)→(r,c+1). Down = same col, row increases by 1: (r,c)→(r+1,c).
5. DRAW n=3: ```row₀: (0,0)→(0,1)→(0,2) row₁: (1,0)→(1,1)→(1,2) row₂: (2,0)→(2,1)→(2,2)``` Start=(0,0), End=(2,2).
6. From (0,0) to (2,2): must go Right 2 times (0→1→2 in col), must go Down 2 times (0→1→2 in row) → total moves = 2+2 = 4.
7. n=3 → moves = (n-1) Right + (n-1) Down = 2(n-1) = 4 moves.
8. n=4 → moves = 3 Right + 3 Down = 6 moves.
9. ENUMERATE n=2 by hand, no blocks: Start=(0,0), End=(1,1). Moves needed: 1 Right, 1 Down.
10. Path₁: (0,0)→Right→(0,1)→Down→(1,1). Sequence: R,D.
11. Path₂: (0,0)→Down→(1,0)→Right→(1,1). Sequence: D,R.
12. Total n=2 no blocks = 2 paths.
13. ENUMERATE n=3 by hand, no blocks: Start=(0,0), End=(2,2). Moves needed: 2 Right (R), 2 Down (D). Total 4 moves.
14. All arrangements of RRDD: RRDD, RDRD, RDDR, DRRD, DRDR, DDRR → count by hand.
15. RRDD: (0,0)→(0,1)→(0,2)→(1,2)→(2,2) ✓
16. RDRD: (0,0)→(0,1)→(1,1)→(1,2)→(2,2) ✓
17. RDDR: (0,0)→(0,1)→(1,1)→(2,1)→(2,2) ✓
18. DRRD: (0,0)→(1,0)→(1,1)→(1,2)→(2,2) ✓
19. DRDR: (0,0)→(1,0)→(1,1)→(2,1)→(2,2) ✓
20. DDRR: (0,0)→(1,0)→(2,0)→(2,1)→(2,2) ✓
21. Total n=3 no blocks = 6 paths.
22. PATTERN: n=2 → 2 paths, n=3 → 6 paths.
23. ENUMERATE n=4 by hand, no blocks: Moves = 3R + 3D = 6 moves total. Write all strings of length 6 with exactly 3 R and 3 D.
24. Start with RRR first, then move D's around: RRRDDD.
25. Move last R one position right: RRDRDD.
26. Move last R one more position right: RRDRD.
27. Move last R one more position right: RRDDDR.
28. Now reset last R, move second R: RDRRD → wait, must have exactly 3R,3D, length 6.
29. Let me be systematic. Write position of each R within 6 positions (1,2,3,4,5,6). Must pick 3 positions for R.
30. Position 1 = first character, Position 2 = second character, ..., Position 6 = sixth character.
31. R at positions 1,2,3 → string = R_R_R_D_D_D → RRRDDD. Trace: (0,0)→R→(0,1)→R→(0,2)→R→(0,3)→D→(1,3)→D→(2,3)→D→(3,3) ✓
32. R at positions 1,2,4 → string = R_R_D_R_D_D → RRDRDD. Trace: (0,0)→R→(0,1)→R→(0,2)→D→(1,2)→R→(1,3)→D→(2,3)→D→(3,3) ✓
33. R at positions 1,2,5 → string = R_R_D_D_R_D → RRDRD. Trace: ✓
34. R at positions 1,2,6 → string = R_R_D_D_D_R → RRDDDR. Trace: ✓
35. R at positions 1,3,4 → string = R_D_R_R_D_D → RDRRDD. Trace: ✓
36. R at positions 1,3,5 → string = R_D_R_D_R_D → RDRDRD. Trace: ✓
37. R at positions 1,3,6 → string = R_D_R_D_D_R → RDRDDR. Trace: ✓
38. R at positions 1,4,5 → string = R_D_D_R_R_D → RDDRRD. Trace: ✓
39. R at positions 1,4,6 → string = R_D_D_R_D_R → RDDRDR. Trace: ✓
40. R at positions 1,5,6 → string = R_D_D_D_R_R → RDDDRR. Trace: ✓
41. R at positions 2,3,4 → string = D_R_R_R_D_D → DRRRDD. Trace: ✓
42. R at positions 2,3,5 → string = D_R_R_D_R_D → DRRDRD. Trace: ✓
43. R at positions 2,3,6 → string = D_R_R_D_D_R → DRRDDR. Trace: ✓
44. R at positions 2,4,5 → string = D_R_D_R_R_D → DRDRRD. Trace: ✓
45. R at positions 2,4,6 → string = D_R_D_R_D_R → DRDRDR. Trace: ✓
46. R at positions 2,5,6 → string = D_R_D_D_R_R → DRDDRR. Trace: ✓
47. R at positions 3,4,5 → string = D_D_R_R_R_D → DDRRRD. Trace: ✓
48. R at positions 3,4,6 → string = D_D_R_R_D_R → DDRRDR. Trace: ✓
49. R at positions 3,5,6 → string = D_D_R_D_R_R → DDRDRR. Trace: ✓
50. R at positions 4,5,6 → string = D_D_D_R_R_R → DDDRRR. Trace: ✓
51. Count: steps 31-50 = 20 distinct strings. Total n=4 no blocks = 20 paths.
52. VERIFY pattern: n=2 → 2, n=3 → 6, n=4 → 20.
53. NOW ADD BLOCKS: n=3, G[1][1]='+'. Some paths from steps 15-20 pass through (1,1).
54. Check each path: RRDD passes (0,0)→(0,1)→(0,2)→(1,2)→(2,2) → (1,1) not visited ✓. RDRD passes (1,1) ✗. RDDR passes (1,1) ✗. DRRD passes (1,1) ✗. DRDR passes (1,1) ✗. DDRR passes (0,0)→(1,0)→(2,0)→(2,1)→(2,2) → (1,1) not visited ✓.
55. Valid paths with block at (1,1) = 2 paths.
56. To reach (3,3) from (0,0): I counted 6 paths (n=4, steps 31-50 reduced or n=3 example).
57. To reach (4,4) from (0,0): I must reach (4,4). (4,4) is bottom-right of 5×5 grid.
58. Last move to (4,4): came from (3,4) via Down OR came from (4,3) via Right.
59. Paths to (4,4) = Paths to (3,4) + Paths to (4,3).
60. To find Paths to (3,4): last move to (3,4) = from (2,4) Down OR from (3,3) Right.
61. Paths to (3,4) = Paths to (2,4) + Paths to (3,3).
62. To find Paths to (4,3): last move to (4,3) = from (3,3) Down OR from (4,2) Right.
63. Paths to (4,3) = Paths to (3,3) + Paths to (4,2).
64. OBSERVE: Paths to (3,3) appears in both step 61 and step 63. Recomputing it twice wastes time.
65. BUILD TABLE: Compute P[r][c] for all (r,c) from (0,0) to (n-1,n-1). Each cell computed once. Reuse values.
66. n=4 example (0-indexed 0..3). Table P[4][4].
67. P[0][0] = 1 (start).
68. Row 0: can only come from left. P[0][0]=1, P[0][1]=P[0][0]=1, P[0][2]=P[0][1]=1, P[0][3]=P[0][2]=1 → Row 0 = [1,1,1,1].
69. Col 0: can only come from top. P[0][0]=1, P[1][0]=P[0][0]=1, P[2][0]=P[1][0]=1, P[3][0]=P[2][0]=1 → Col 0 = [1,1,1,1].
70. P[1][1] = P[0][1] + P[1][0] = 1 + 1 = 2.
71. P[1][2] = P[0][2] + P[1][1] = 1 + 2 = 3.
72. P[1][3] = P[0][3] + P[1][2] = 1 + 3 = 4.
73. P[2][1] = P[1][1] + P[2][0] = 2 + 1 = 3.
74. P[2][2] = P[1][2] + P[2][1] = 3 + 3 = 6.
75. P[2][3] = P[1][3] + P[2][2] = 4 + 6 = 10.
76. P[3][1] = P[2][1] + P[3][0] = 3 + 1 = 4.
77. P[3][2] = P[2][2] + P[3][1] = 6 + 4 = 10.
78. P[3][3] = P[2][3] + P[3][2] = 10 + 10 = 20 ✓ matches step 51.
79. DRAW TABLE n=4: ```+----+----+----+----+ |  1 |  1 |  1 |  1 | row 0 +----+----+----+----+ |  1 |  2 |  3 |  4 | row 1 +----+----+----+----+ |  1 |  3 |  6 | 10 | row 2 +----+----+----+----+ |  1 |  4 | 10 | 20 | row 3 +----+----+----+----+```
80. VERIFY step 59: Paths to (4,4) in 1-indexed = P[3][3] in 0-indexed = 20 ✓.
81. Recurrence: P[r][c] = P[r-1][c] + P[r][c-1].
82. Boundary: r=0 → P[0][c] = P[0][c-1]. c=0 → P[r][0] = P[r-1][0].
83. If G[r][c] = '+' → P[r][c] = 0 (blocked, cannot land).
61. CALCULATE P for n=3 with block at (1,1):
62. P[0][0] = 1.
63. P[0][1] = P[0][0] = 1 (only from left, boundary).
64. P[0][2] = P[0][1] = 1.
65. P[1][0] = P[0][0] = 1 (only from top, boundary).
66. P[1][1] = 0 (blocked by '+').
67. P[1][2] = P[0][2] + P[1][1] = 1 + 0 = 1.
68. P[2][0] = P[1][0] = 1.
69. P[2][1] = P[1][1] + P[2][0] = 0 + 1 = 1.
70. P[2][2] = P[1][2] + P[2][1] = 1 + 1 = 2 ✓ matches step 55.
71. EXERCISE 1: n=2, G=[[.,.],[.,.]] → FILL P table by hand. Expected = 2.
72. EXERCISE 2: n=2, G=[[.,+],[.,.]] → (0,1) blocked → FILL P table. Expected = 1.
73. EXERCISE 3: n=4, no blocks → FILL P[4][4] table by hand. Final P[3][3] should = 20 (step 51).
74. EXERCISE 4: n=3, G[0][0]='+' → Start blocked → P[0][0]=0 → all downstream = 0 → Output = 0.
75. EXERCISE 5: n=3, G[2][2]='+' → End blocked → P[2][2]=0 regardless of paths → Output = 0.
76. SPACE OPTIMIZATION: O(n²) table → O(n) single row. B[c] = paths to current row, col c. Update left-to-right.
77. B[c] before update = P[r-1][c] (top). B[c-1] after update = P[r][c-1] (left). B[c] = B[c] + B[c-1].
78. TRACE O(n) for n=3 with block: B=[0,0,0]. B[0]=1. Row₀: B=[1,1,1]. Row₁: B[0]=1, B[1]=0(blocked), B[2]=1+0=1 → B=[1,0,1]. Row₂: B[0]=1, B[1]=0+1=1, B[2]=1+1=2 → B=[1,1,2]. Output=2 ✓.
79. TIME: O(n²) = n rows × n cols × O(1) per cell.
80. SPACE: O(n) = single row buffer of size n.
81. F1: Enumerate all paths → 2^(2n-2) ✗ TLE for large n.
82. F2: Forget boundary check → access index -1 ✗ crash.
83. F3: Forget blocked check → count paths through '+' ✗ wrong.
84. F4: Forget P[0][0]=0 when G[0][0]='+' → propagate 1s incorrectly ✗.
85. F5: 1-indexed vs 0-indexed confusion → off-by-one ✗.
86. F6: Integer overflow for large n → use unsigned long long.
87. F7: Update B[c] before checking block → should zero first if blocked.

USER MISTAKES 2025-12-13:
E1: Line 13 → dp(n, vector(n+1, 0)) → creates n rows (0..n-1), n+1 cols (0..n) → dp[n][n] access at line 28 → row n does not exist → out of bounds.
E2: Line 13 → why n+1 cols? → confused 0-indexed with 1-indexed → should be dp(n, vector(n, 0)).
E3: Line 21 → for i=1 to n → dp[n][j] accessed → row n does not exist → should be i=1 to n-1.
E4: Line 23 → for j=1 to n → dp[i][n] accessed → should be j=1 to n-1.
E5: Line 28 → return dp[n][n] → should be dp[n-1][n-1].
E6: Line 15-19 → dp[i][0]=1, dp[0][i]=1 → no check if grid[i][0]=='+' or grid[0][i]=='+' → blocked cells get 1 instead of 0.
E7: Line 25 → dp[i][j]=dp[i-1][j]+dp[i][j-1] → no check if grid[i][j]=='+' → blocked cells get sum instead of 0.
E8: Line 14 → dp[0][0]=1 → no check if grid[0][0]=='+' → start blocked should be 0.
SLOPPY PATTERN: Used 1-indexed loop bounds (1..n) with 0-indexed array (0..n-1) → classic off-by-one.
SLOPPY PATTERN: Ignored grid entirely → wrote path counting without obstacle check.
SLOPPY PATTERN: Did not trace test case 1 by hand before writing code → would have caught E6-E8 immediately.
PREVENTION: Before coding, trace n=3 blocked example: grid[1][1]='+' → P[1][1]=0 → verify code sets dp[1][1]=0.

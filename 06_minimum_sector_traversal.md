# Minimum Sector Traversal - Axiomatic Derivation

01. INPUT DATA: sectors=[50, 80, 70], disk=100 (0-99), start=0, max_reversal=1 → GOAL: Min distance to traverse all.
02. PRE-PROCESS: Filter 0, Sort, Dedupe → S=[50, 70, 80] (N=3). s₁=50, sₙ=80.
03. STRATEGY CW_ONLY: 0 → sₙ (CW) covers [0, sₙ]. Cost = sₙ = 80.
04. STRATEGY CCW_ONLY: 0 → s₁ (CCW) covers [s₁, 0]. Cost = 100 - s₁ = 100 - 50 = 50.
05. STRATEGY PARTITION: Iterate gaps (sᵢ, sᵢ₊₁) to split traversal into CW-first and CCW-first segments.
06. GAP 1 (50, 70): i=0, Left=50, Right=70.
    06a. CW_THEN_CCW: 0→50 (CW), Reverse, 50→70 (CCW). Path: 0..50 (CW) then 50..0..80..70 (CCW).
         Cost = 50 + (50 + 100 - 70) = 2*50 + 30 = 130.
    06b. CCW_THEN_CW: 0→70 (CCW), Reverse, 70→50 (CW). Path: 0..80..70 (CCW) then 70..80..0..50 (CW).
         Cost = (100-70) + (100-70 + 50) = 2*30 + 50 = 110.
07. GAP 2 (70, 80): i=1, Left=70, Right=80.
    07a. CW_THEN_CCW: 0→70 (CW), Reverse, 70→80 (CCW). Path: 0..70 then 70..0..80.
         Cost = 2*70 + (100-80) = 140 + 20 = 160.
    07b. CCW_THEN_CW: 0→80 (CCW), Reverse, 80→70 (CW). Path: 0..80 then 80..0..70.
         Cost = 2*(100-80) + 70 = 40 + 70 = 110.
08. MINIMIZE: min(80, 50, 130, 110, 160, 110) → 50. ✓ (Matches User Ex 1).

09. INPUT DATA 2: sectors=[10, 70, 60] → Sort → S=[10, 60, 70]. s₁=10, sₙ=70.
10. CW_ONLY: 70.
11. CCW_ONLY: 100 - 10 = 90.
12. GAP 1 (10, 60): Left=10, Right=60.
    12a. CW_THEN_CCW: 2*10 + (100-60) = 20 + 40 = 60.
    12b. CCW_THEN_CW: 2*(100-60) + 10 = 80 + 10 = 90.
13. GAP 2 (60, 70): Left=60, Right=70.
    13a. CW_THEN_CCW: 2*60 + (100-70) = 120 + 30 = 150.
    13b. CCW_THEN_CW: 2*(100-70) + 60 = 60 + 60 = 120.
14. MINIMIZE: min(70, 90, 60, 90, 150, 120) → 60. ✓ (Matches User Ex 2).

15. TEST 1 TRACE {55, 12, 90, 3, 25} → S=[3, 12, 25, 55, 90].
16. CW=90. CCW=97.
17. GAP (55, 90): Left=55, Right=90.
    17a. CCW_THEN_CW: 2*(100-90) + 55 = 2*10 + 55 = 75.
    75 < 90 → Min=75. ✓

18. TRAP OF MEMORIZATION: Assuming min is always simple CW or CCW.
19. TRAP OF LOGIC: Assuming reversal always happens at s₁ or sₙ. Iterating all gaps is mandatory.
20. TRAP OF ZERO: Sector 0 contributes nothing to distance but can break sorting if not filtered.
21. FORMULA: Res = min(S.back(), 100-S.front(), min_over_i(2*S[i] + 100 - S[i+1]), min_over_i(2*(100 - S[i+1]) + S[i])).

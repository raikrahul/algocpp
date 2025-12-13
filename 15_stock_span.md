01. INPUT: A[0..4]={6,3,4,5,2} → n=5 → indices {0,1,2,3,4} → OUTPUT: S[0..4]={1,1,2,3,1}
02. DEFINITION: S[i] = count of consecutive elements A[j] immediately before A[i] where A[j]≤A[i], including A[i] itself → minimum S[i]=1 (element counts itself)
03. BRUTE FORCE i=0: A[0]=6 → no j<0 exists → count=1 → S[0]=1
04. BRUTE FORCE i=1: A[1]=3 → check j=0 → A[0]=6 → 6≤3? → 6>3 ✗ stop → count=1 → S[1]=1
05. BRUTE FORCE i=2: A[2]=4 → check j=1 → A[1]=3 → 3≤4? → 3<4 ✓ continue → check j=0 → A[0]=6 → 6≤4? → 6>4 ✗ stop → count=2 → S[2]=2
06. BRUTE FORCE i=3: A[3]=5 → check j=2 → A[2]=4 → 4≤5? ✓ → check j=1 → A[1]=3 → 3≤5? ✓ → check j=0 → A[0]=6 → 6≤5? ✗ stop → count=3 → S[3]=3
07. BRUTE FORCE i=4: A[4]=2 → check j=3 → A[3]=5 → 5≤2? ✗ stop → count=1 → S[4]=1
08. BRUTE FORCE COST: i=0→0 checks, i=1→1 check, i=2→2 checks, i=3→3 checks, i=4→1 check → total=7 → worst case O(n²) when array descending
09. OBSERVE i=3: A[3]=5 → checked A[2]=4, A[1]=3, stopped at A[0]=6 → A[0]=6 is first element > A[3] going left → index 0 is the "stopper" for index 3
10. OBSERVE i=2: A[2]=4 → stopped at A[0]=6 → same stopper → multiple elements share same stopper
11. CALCULATE SPAN FORMULA: S[i] = i - (index of nearest left element > A[i]) → if no such element exists, S[i] = i+1
12. TRACE i=3: stopper index=0 → S[3] = 3-0 = 3 ✓ matches expected
13. TRACE i=2: stopper index=0 → S[2] = 2-0 = 2 ✓ matches expected
14. TRACE i=1: stopper index=0 → S[1] = 1-0 = 1 ✓ matches expected
15. TRACE i=0: no stopper → S[0] = 0-(-1) = 0+1 = 1 ✓ matches expected (use -1 as sentinel)
16. QUESTION: How to find "nearest left element > A[i]" efficiently without scanning all left elements?

17. YOU FILL: What data structure maintains "candidates" for stopper as you scan left to right? stack I think 
18. YOU FILL: When processing A[i], which previous indices are no longer useful candidates? all which are less more than A[i]
19. YOU FILL: If A[j] ≤ A[i] and j < i, will A[j] ever be stopper for any future k > i? let's say j is 1 and i is 2, then 
20. YOU FILL: Draw stack contents after processing each index for A={6,3,4,5,2}
21. YOU FILL: Write the while loop condition that pops useless candidates
22. YOU FILL: Write the span calculation using stack.top() or empty stack case

23. EDGE N=1: A={7} → S={1} → only element, span=1
24. EDGE ASCENDING: A={1,2,3,4} → S={1,2,3,4} → each element spans all previous
25. EDGE DESCENDING: A={4,3,2,1} → S={1,1,1,1} → each element blocked by immediate predecessor
26. EDGE PLATEAU: A={5,5,5,5} → S={1,2,3,4} → equal elements count toward span (≤ not <)
27. EDGE SINGLE PEAK: A={1,2,3,2,1} → S={1,2,3,1,1} → peak blocks nothing after it

:00 FAILURE F1: Use < instead of ≤ → plateau cases wrong → A={5,5} gives S={1,1} instead of S={1,2}
:01 FAILURE F2: Pop when A[stack.top()] < A[i] instead of ≤ → span undercounted
:02 FAILURE F3: Forget to push current index after computing span → future elements miss candidate
:03 FAILURE F4: Empty stack check missing → stack.top() on empty → undefined behavior
:04 FAILURE F5: Off-by-one in span formula → S[i] = i - stopper vs i - stopper - 1 confusion

═══════════════════════════════════════════════════════════════════════
ERROR REPORT
═══════════════════════════════════════════════════════════════════════

E1. LINE 21 → wrote `<` → should be `<=`
    WHY SLOPPY: confused stopper condition (>) with discard condition (≤)
    MISSED: span counts A[j] ≤ A[i], stopper is A[j] > A[i], discard when NOT stopper
    PREVENT: write span definition first, derive conditions from definition

E2. BRAIN FREEZE → could not see stack in problem
    WHY SLOPPY: jumped to solution without deriving data structure need
    MISSED: scan order = most recent first = LIFO = stack
    PREVENT: trace operations first (add, check, remove), then pick structure

E3. CONFUSION → thought "keep greater" means keep all greater values
    WHY SLOPPY: mixed up "useful for future" vs "stopper for current"
    MISSED: add current always, discard when current proves old useless
    PREVENT: separate two actions: (1) find stopper for i, (2) prepare for i+1

E4. CONFUSION → thought empty stack back to S1 in queue problem
    WHY SLOPPY: over-generalized "transfer" concept from queue problem
    MISSED: each problem has different invariants
    PREVENT: re-derive for each problem, do not copy patterns blindly

E5. READING SKIP → glossed over "≤" vs "<" in problem definition
    WHY SLOPPY: 3 decades of skimming
    MISSED: A[j] ≤ A[i] counts toward span, not A[j] < A[i]
    PREVENT: underline/highlight comparison operators in problem statement

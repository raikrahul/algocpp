01. d[]={5,3,4,2,6}, n=5, M=7 → s₁→s₂→s₃→s₄→s₅ → distances: 0→5→8→12→14→20 → cumulative positions from Pune
02. Tank holds M=7 miles → at s₁ (Pune) tank=7 → drive 5 miles → arrive s₂ with tank=2 → DECISION: refuel or skip? → 2<3 (next leg) → must refuel → stops=1
03. F1: You will forget tank depletes DURING travel, not AT station → tank=7, drive d[1]=5 → tank=7-5=2 at s₂, not 7 → FAILURE MODE: skipping subtraction
04. F2: You will check "can I reach next?" AFTER arrival → wrong → check BEFORE departure → at s₂ with tank=2, next leg=3 → 2<3 → refuel NOW, not later
05. F3: You will confuse d[i] = distance FROM s[i-1] TO s[i] → d[1]=5 means s₁→s₂ is 5 miles, NOT s₂→s₃ → d[i] brings you TO s[i]
06. F4: You will try to track partial tank values → trap → greedy: refuel only when tank < d[next] → tank resets to M=7 on refuel
07. F5: You will loop i=1 to n → wrong → loop i=2 to n (s₁ is START, not stop) → s₁=Pune=start, sₙ=Mumbai=end → count stops BETWEEN
08. |i=1|i=2|i=3|i=4|i=5| → |s₁|s₂|s₃|s₄|s₅| → d[]={_,5,3,4,2,6} → d[2]=5=distance s₁→s₂, d[3]=3=distance s₂→s₃, d[4]=4, d[5]=2, d[6]=6 → WAIT: n=5 stations, d[] has indices 1..n-1 for distances BETWEEN → TRAP: array indexing
09. REREAD: "d[i] ≤ M" means each leg is reachable → no leg exceeds tank capacity → problem is solvable for all valid inputs
10. TRACE EXAMPLE 1: d[]={5,3,4,2}, n=5, M=7 → 4 distance values for 5 stations → positions: 0,5,8,12,14 → at s₁(pos=0): tank=7 → drive d[1]=5 → at s₂(pos=5): tank=7-5=2 → 2<d[2]=3 → refuel→tank=7, stops=1 → drive d[2]=3 → at s₃(pos=8): tank=7-3=4 → 4≥d[3]=4 → no refuel → drive d[3]=4 → at s₄(pos=12): tank=4-4=0 → 0<d[4]=2 → refuel→tank=7, stops=2 → drive d[4]=2 → at s₅(pos=14): tank=7-2=5 → ARRIVED → stops=2 ✓
11. TRACE EXAMPLE 2: d[]={2,2,2,2}, n=5, M=7 → positions: 0,2,4,6,8 → tank=7 → d[1]=2→tank=5 → 5≥2 ✓ → d[2]=2→tank=3 → 3≥2 ✓ → d[3]=2→tank=1 → 1<2 ✗ → refuel→tank=7, stops=1 → d[4]=2→tank=5 → ARRIVED → stops=1 ✓
12. TRACE EXAMPLE 3: d[]={7,7,7}, n=4, M=7 → tank=7 → d[1]=7→tank=0 → 0<7 ✗ → refuel→tank=7, stops=1 → d[2]=7→tank=0 → 0<7 ✗ → refuel→tank=7, stops=2 → d[3]=7→tank=0 → ARRIVED → stops=2 ✓
13. TRACE EXAMPLE 4: d[]={1,1,1,1,1,1,1}, n=8, M=7 → tank=7 → d[1]=1→tank=6 → d[2]=1→tank=5 → d[3]=1→tank=4 → d[4]=1→tank=3 → d[5]=1→tank=2 → d[6]=1→tank=1 → 1≥d[7]=1 ✓ → d[7]=1→tank=0 → ARRIVED → stops=0 ✓ → GREEDY WORKS: drove 7 miles on one tank
14. TRACE EXAMPLE 5: d[]={6}, n=2, M=7 → tank=7 → d[1]=6→tank=1 → ARRIVED → stops=0 ✓ → EDGE: only one leg
15. TRACE EXAMPLE 6: d[]={7}, n=2, M=7 → tank=7 → d[1]=7→tank=0 → ARRIVED → stops=0 ✓ → EDGE: exactly empty on arrival
16. TRACE EXAMPLE 7: d[]={6,6,6}, n=4, M=7 → tank=7 → d[1]=6→tank=1 → 1<6 ✗ → refuel→tank=7, stops=1 → d[2]=6→tank=1 → 1<6 ✗ → refuel→tank=7, stops=2 → d[3]=6→tank=1 → ARRIVED → stops=2 ✓
17. F6: You will write: if(tank < d[i]) { refuel; tank -= d[i]; } → WRONG ORDER → must refuel THEN subtract → refuel sets tank=M, then tank=M-d[i]
18. F7: You will forget to subtract distance AFTER checking → tank ≥ d[i] → still must drive → tank -= d[i] → happens AFTER check
19. F8: You will return stops BEFORE reaching sₙ → loop must complete all n-1 legs → return stops only after index=n-1 or i=n (depending on loop)
20. ALGORITHM: tank=M, stops=0 → for i=1 to n-1: if tank<d[i] then tank=M, stops++ → tank-=d[i] → return stops
21. COMPLEXITY: O(n) time (single loop n-1 iterations) → O(1) space (3 integers: tank, stops, i)
22. EDGE n=1: no legs to drive → d[] empty → stops=0 → loop body never executes
23. EDGE n=2: one leg d[1] → if d[1]≤M (guaranteed) → tank=M → M≥d[1] always true → tank=M-d[1]≥0 → stops=0 UNLESS d[1]=M AND you start checking wrong
24. VERIFY: greedy is optimal → proof: delaying a stop never helps → if you skip refueling at sᵢ and run empty before sⱼ → you must backtrack (impossible) → ∴ refuel at first station where tank<d[next] is optimal
25. |step|station|tank_before|d[i]|tank<d[i]?|refuel?|tank_after|stops|
26. |1|s₂|7|5|7<5=✗|no|7-5=2|0|
27. |2|s₃|2|3|2<3=✓|yes→7|7-3=4|1|
28. |3|s₄|4|4|4<4=✗|no|4-4=0|1|
29. |4|s₅|0|2|0<2=✓|yes→7|7-2=5|2|
30. FINAL: stops=2 for d[]={5,3,4,2}, M=7, n=5
31. INPUT FORMAT TRAP: problem says d[i] is distance from s[i-1] to s[i] for 2≤i≤n → array is 1-indexed in problem → your code may be 0-indexed → d[0] in code = d[1] in problem = distance s₁→s₂
32. LOOP IN 0-INDEXED CODE: for(int i=0; i<n-1; i++) → d[i] in code = distance from station i to station i+1 → n-1 distances for n stations
33. FUNCTION SIGNATURE: int FindMinStops(int d[], int n, int m) → d[]=distances (n-1 values or n values with d[0] unused?), n=station count, m=tank capacity → MUST CLARIFY: does d have n-1 elements (one per leg) or n elements (d[0] unused)?
34. ASSUME: d has n-1 elements indexed 0..n-2 → d[i] = distance from station i to station i+1 → code: for(i=0; i<n-1; i++) process d[i]
35. WRITE BY HAND: tank=m=7, stops=0 → i=0: d[0]=5 → 7<5? ✗ → tank=7-5=2, stops=0 → i=1: d[1]=3 → 2<3? ✓ → tank=7, stops=1 → tank=7-3=4, stops=1 → i=2: d[2]=4 → 4<4? ✗ → tank=4-4=0, stops=1 → i=3: d[3]=2 → 0<2? ✓ → tank=7, stops=2 → tank=7-2=5, stops=2 → loop ends → return 2 ✓
36. FRACTIONAL THINKING TRAP: M=7, d[]={3.5,3.5} → tank=7 → 7-3.5=3.5 → 3.5≥3.5 ✓ → 3.5-3.5=0 → stops=0 → BUT: problem uses integers → no fractions → you will still THINK fractionally and make errors
37. STRESS TEST: n=1000, all d[i]=1, M=1000 → each leg uses 1 → 999 legs → tank=1000-999=1 at end → stops=0 → O(n)=O(1000) ✓
38. STRESS TEST 2: n=1000, all d[i]=1000, M=1000 → each leg drains tank → after d[0]: tank=0 → 0<1000 → refuel at every station → stops=998 (not 999: last arrival needs no refuel)
39. F9: You will count refuel at destination → WRONG → sₙ=Mumbai=destination → no refuel needed after arrival → loop i=0 to n-2 prevents this
40. F10: You will initialize tank=0 instead of tank=M → start at s₁ with FULL tank → tank=M initially
41. MENTAL MODEL: |Pune=s₁|---d[0]---|s₂|---d[1]---|s₃|---d[2]---|sₙ=Mumbai| → n stations, n-1 distances → tank decreases during travel, refills at stations
42. DO BY HAND: m=10, d[]={3,5,6,2,8,1}, n=7 → tank=10 → d[0]=3→tank=7 → 7≥5 ✓ → d[1]=5→tank=2 → 2<6 ✗ → refuel→tank=10, stops=1 → d[2]=6→tank=4 → 4≥2 ✓ → d[3]=2→tank=2 → 2<8 ✗ → refuel→tank=10, stops=2 → d[4]=8→tank=2 → 2≥1 ✓ → d[5]=1→tank=1 → ARRIVED → stops=2 ✓
43. DO BY HAND: m=5, d[]={4,4,4,4}, n=5 → tank=5 → d[0]=4→tank=1 → 1<4 ✗ → refuel→tank=5, stops=1 → d[1]=4→tank=1 → 1<4 ✗ → refuel→tank=5, stops=2 → d[2]=4→tank=1 → 1<4 ✗ → refuel→tank=5, stops=3 → d[3]=4→tank=1 → ARRIVED → stops=3 ✓
44. SURPRISE: stops = count of times tank<d[i] evaluates true → count trues → O(n) loop with O(1) check
45. CODE SKELETON: int FindMinStops(int d[], int n, int m) { int tank = m, stops = 0; for(int i = 0; i < n-1; i++) { if(tank < d[i]) { tank = m; stops++; } tank -= d[i]; } return stops; }

# 20. N-Length Permutations

---

1. s="ABC" → n=3 → output count = ? → 3×2×1 = 6 → fill: first slot =  3 choices, second slot = 2 choices, third slot = 1 choice → 3×2×1=6 ✓

2. s="ABCD" → n=4 → 4×3×2×1 = 24 → s="12345" → 5×4×3×2×1 = 120 → pattern: n! = n×(n-1)×...×1

---

3. draw used[] array for s="ABC": `used[0]=F used[1]=F used[2]=F` → index 0→'A', index 1→'B', index 2→'C' → used[i]=T means s[i] already picked → fill below:
```
┌───────┬───────┬───────┐
│ idx=0 │ idx=1 │ idx=2 │
│  'A'  │  'B'  │  'C'  │
│ used? │ used? │ used? │
│   F   │   F   │   F   │
└───────┴───────┴───────┘
current = ""
depth = 0
```

4. depth=0 current="" used={F,F,F} → loop i=0,1,2 → pick i=0 → used[0]→T current→"A" depth→1 → draw state:
```
┌───────┬───────┬───────┐
│   T   │   F   │   F   │
└───────┴───────┴───────┘
current = "A"      depth = 1
```

5. depth=1 current="A" used={T,F,F} → loop i=0,1,2 → i=0: used[0]=T → skip ✗ → i=1: used[1]=F → pick ✓ → used[1]→T current→"AB" depth→2 → draw:
```
┌───────┬───────┬───────┐
│   T   │   T   │   F   │
└───────┴───────┴───────┘
current = "AB"     depth = 2
```

6. depth=2 current="AB" used={T,T,F} → loop i=0,1,2 → i=0: T skip → i=1: T skip → i=2: F pick → used[2]→T current→"ABC" depth→3 → draw:
```
┌───────┬───────┬───────┐
│   T   │   T   │   T   │
└───────┴───────┴───────┘
current = "ABC"    depth = 3
```

7. depth=3 → depth==n ✓ → OUTPUT "ABC" → return → BACKTRACK: used[2]→F current.pop→"AB" → draw after backtrack:
```
┌───────┬───────┬───────┐
│   T   │   T   │   F   │
└───────┴───────┴───────┘
current = "AB"     depth = 2     OUTPUT₁ = "ABC"
```

8. back at depth=2 → loop continues i=3 → i<n ? → 3<3 ✗ → loop done → return → BACKTRACK: used[1]→F current.pop→"A" → draw:
```
┌───────┬───────┬───────┐
│   T   │   F   │   F   │
└───────┴───────┴───────┘
current = "A"      depth = 1     OUTPUT₁ = "ABC"
```

9. back at depth=1 → loop continues i=2 → used[2]=F ✓ → pick → used[2]→T current→"AC" depth→2 → draw:
```
┌───────┬───────┬───────┐
│   T   │   F   │   T   │
└───────┴───────┴───────┘
current = "AC"     depth = 2
```

10. depth=2 current="AC" → i=0: T skip → i=1: F pick → used[1]→T current→"ACB" depth→3 → depth==n ✓ → OUTPUT "ACB" → BACKTRACK → draw:
```
┌───────┬───────┬───────┐
│   T   │   F   │   T   │
└───────┴───────┴───────┘
current = "AC"     depth = 2     OUTPUT₂ = "ACB"
```

---

11. FULL DEBUGGER TRACE for s="AB" n=2 (line numbers reference implemented perm_helper)
```
REFERENCE CODE (lines 37-50):
37: void perm_helper(const string& s, int n, int depth, string& current, vector<bool>& used, vector<string>& result) {
38:   if (depth == n) {
39:     result.push_back(current);
40:     return;
41:   }
42:   for (int i = 0; i < n; i++) {
43:     if (!used[i]) {
44:       used[i] = true;
45:       current.push_back(s[i]);
46:       perm_helper(s, n, depth + 1, current, used, result);
47:       current.pop_back();
48:       used[i] = false;
49:     }
50:   }
51: }
```

```
#01. CALL. line:68→37. caller=permutations. depth=0, current="", used={F,F}, result={}. entering perm_helper first time.
     s="AB" n=2 depth=0 current="" used[0]=F used[1]=F result.size=0

#02. LINE:38. depth==n? → 0==2? → F. skip base case.
     depth=0 n=2 → 0≠2 → continue to loop

#03. LINE:42. loop start. i=0. i<n? → 0<2? → T. enter loop body.
     i=0 n=2 → 0<2 ✓

#04. LINE:43. !used[i]? → !used[0]? → !F? → T. enter if-block.
     used[0]=F → !F=T → condition passes

#05. LINE:44. used[i]=true → used[0]=true.
     BEFORE: used={F,F} → AFTER: used={T,F}

#06. LINE:45. current.push_back(s[i]) → current.push_back(s[0]) → current.push_back('A').
     BEFORE: current="" → AFTER: current="A"

#07. CALL. line:46→37. caller=line46. depth=1, current="A", used={T,F}, result={}. recursive call.
     s="AB" n=2 depth=1 current="A" used[0]=T used[1]=F result.size=0

#08. LINE:38. depth==n? → 1==2? → F. skip base case.
     depth=1 n=2 → 1≠2 → continue to loop

#09. LINE:42. loop start. i=0. i<n? → 0<2? → T. enter loop body.
     i=0 n=2 → 0<2 ✓

#10. LINE:43. !used[i]? → !used[0]? → !T? → F. skip if-block.
     used[0]=T → !T=F → condition fails → skip to next i

#11. LINE:42. loop continue. i++ → i=1. i<n? → 1<2? → T. enter loop body.
     i=1 n=2 → 1<2 ✓

#12. LINE:43. !used[i]? → !used[1]? → !F? → T. enter if-block.
     used[1]=F → !F=T → condition passes

#13. LINE:44. used[i]=true → used[1]=true.
     BEFORE: used={T,F} → AFTER: used={T,T}

#14. LINE:45. current.push_back(s[i]) → current.push_back(s[1]) → current.push_back('B').
     BEFORE: current="A" → AFTER: current="AB"

#15. CALL. line:46→37. caller=line46. depth=2, current="AB", used={T,T}, result={}. recursive call.
     s="AB" n=2 depth=2 current="AB" used[0]=T used[1]=T result.size=0

#16. LINE:38. depth==n? → 2==2? → T. enter base case.
     depth=2 n=2 → 2==2 ✓ → BASE CASE TRIGGERED

#17. LINE:39. result.push_back(current) → result.push_back("AB").
     BEFORE: result={} → AFTER: result={"AB"}
     ★ OUTPUT₁ = "AB" ★

#18. LINE:40. return. exit function. resume caller at line 46.
     returning to call#15's caller at line 46

#19. RESUMED. line:46→47. resumed from call#15. depth=1, current="AB", used={T,T}, result={"AB"}. continue after recursive call.
     back at depth=1, i=1 loop iteration

#20. LINE:47. current.pop_back().
     BEFORE: current="AB" → AFTER: current="A"

#21. LINE:48. used[i]=false → used[1]=false.
     BEFORE: used={T,T} → AFTER: used={T,F}

#22. LINE:42. loop continue. i++ → i=2. i<n? → 2<2? → F. exit loop.
     i=2 n=2 → 2<2 ✗ → loop done

#23. LINE:51. implicit return. exit function. resume caller at line 46.
     returning to call#07's caller at line 46

#24. RESUMED. line:46→47. resumed from call#07. depth=0, current="A", used={T,F}, result={"AB"}. continue after recursive call.
     back at depth=0, i=0 loop iteration

#25. LINE:47. current.pop_back().
     BEFORE: current="A" → AFTER: current=""

#26. LINE:48. used[i]=false → used[0]=false.
     BEFORE: used={T,F} → AFTER: used={F,F}

#27. LINE:42. loop continue. i++ → i=1. i<n? → 1<2? → T. enter loop body.
     i=1 n=2 → 1<2 ✓

#28. LINE:43. !used[i]? → !used[1]? → !F? → T. enter if-block.
     used[1]=F → !F=T → condition passes

#29. LINE:44. used[i]=true → used[1]=true.
     BEFORE: used={F,F} → AFTER: used={F,T}

#30. LINE:45. current.push_back(s[i]) → current.push_back(s[1]) → current.push_back('B').
     BEFORE: current="" → AFTER: current="B"

#31. CALL. line:46→37. caller=line46. depth=1, current="B", used={F,T}, result={"AB"}. recursive call.
     s="AB" n=2 depth=1 current="B" used[0]=F used[1]=T result.size=1

#32. LINE:38. depth==n? → 1==2? → F. skip base case.
     depth=1 n=2 → 1≠2 → continue to loop

#33. LINE:42. loop start. i=0. i<n? → 0<2? → T. enter loop body.
     i=0 n=2 → 0<2 ✓

#34. LINE:43. !used[i]? → !used[0]? → !F? → T. enter if-block.
     used[0]=F → !F=T → condition passes

#35. LINE:44. used[i]=true → used[0]=true.
     BEFORE: used={F,T} → AFTER: used={T,T}

#36. LINE:45. current.push_back(s[i]) → current.push_back(s[0]) → current.push_back('A').
     BEFORE: current="B" → AFTER: current="BA"

#37. CALL. line:46→37. caller=line46. depth=2, current="BA", used={T,T}, result={"AB"}. recursive call.
     s="AB" n=2 depth=2 current="BA" used[0]=T used[1]=T result.size=1

#38. LINE:38. depth==n? → 2==2? → T. enter base case.
     depth=2 n=2 → 2==2 ✓ → BASE CASE TRIGGERED

#39. LINE:39. result.push_back(current) → result.push_back("BA").
     BEFORE: result={"AB"} → AFTER: result={"AB","BA"}
     ★ OUTPUT₂ = "BA" ★

#40. LINE:40. return. exit function. resume caller at line 46.
     returning to call#37's caller at line 46

#41. RESUMED. line:46→47. resumed from call#37. depth=1, current="BA", used={T,T}, result={"AB","BA"}. continue after recursive call.
     back at depth=1, i=0 loop iteration

#42. LINE:47. current.pop_back().
     BEFORE: current="BA" → AFTER: current="B"

#43. LINE:48. used[i]=false → used[0]=false.
     BEFORE: used={T,T} → AFTER: used={F,T}

#44. LINE:42. loop continue. i++ → i=1. i<n? → 1<2? → T. enter loop body.
     i=1 n=2 → 1<2 ✓

#45. LINE:43. !used[i]? → !used[1]? → !T? → F. skip if-block.
     used[1]=T → !T=F → condition fails → skip to next i

#46. LINE:42. loop continue. i++ → i=2. i<n? → 2<2? → F. exit loop.
     i=2 n=2 → 2<2 ✗ → loop done

#47. LINE:51. implicit return. exit function. resume caller at line 46.
     returning to call#31's caller at line 46

#48. RESUMED. line:46→47. resumed from call#31. depth=0, current="B", used={F,T}, result={"AB","BA"}. continue after recursive call.
     back at depth=0, i=1 loop iteration

#49. LINE:47. current.pop_back().
     BEFORE: current="B" → AFTER: current=""

#50. LINE:48. used[i]=false → used[1]=false.
     BEFORE: used={F,T} → AFTER: used={F,F}

#51. LINE:42. loop continue. i++ → i=2. i<n? → 2<2? → F. exit loop.
     i=2 n=2 → 2<2 ✗ → loop done

#52. LINE:51. implicit return. exit function. return to permutations line 68.
     perm_helper complete. result={"AB","BA"}

FINAL: result={"AB","BA"} → 2 outputs = 2! ✓
```

---

12. SUMMARY TABLE for s="AB" trace:
```
| #  | type    | line | depth | i   | current | used    | result         | action                    |
|----|---------|------|-------|-----|---------|---------|----------------|---------------------------|
| 01 | CALL    | →37  | 0     | -   | ""      | {F,F}   | {}             | enter perm_helper         |
| 05 | EXEC    | 44   | 0     | 0   | ""      | {T,F}   | {}             | used[0]=true              |
| 06 | EXEC    | 45   | 0     | 0   | "A"     | {T,F}   | {}             | push 'A'                  |
| 07 | CALL    | →37  | 1     | -   | "A"     | {T,F}   | {}             | recurse depth+1           |
| 13 | EXEC    | 44   | 1     | 1   | "A"     | {T,T}   | {}             | used[1]=true              |
| 14 | EXEC    | 45   | 1     | 1   | "AB"    | {T,T}   | {}             | push 'B'                  |
| 15 | CALL    | →37  | 2     | -   | "AB"    | {T,T}   | {}             | recurse depth+1           |
| 17 | EXEC    | 39   | 2     | -   | "AB"    | {T,T}   | {"AB"}         | ★ OUTPUT "AB"             |
| 18 | RET     | 40   | 2     | -   | "AB"    | {T,T}   | {"AB"}         | return                    |
| 20 | EXEC    | 47   | 1     | 1   | "A"     | {T,T}   | {"AB"}         | pop_back                  |
| 21 | EXEC    | 48   | 1     | 1   | "A"     | {T,F}   | {"AB"}         | used[1]=false             |
| 25 | EXEC    | 47   | 0     | 0   | ""      | {T,F}   | {"AB"}         | pop_back                  |
| 26 | EXEC    | 48   | 0     | 0   | ""      | {F,F}   | {"AB"}         | used[0]=false             |
| 29 | EXEC    | 44   | 0     | 1   | ""      | {F,T}   | {"AB"}         | used[1]=true              |
| 30 | EXEC    | 45   | 0     | 1   | "B"     | {F,T}   | {"AB"}         | push 'B'                  |
| 31 | CALL    | →37  | 1     | -   | "B"     | {F,T}   | {"AB"}         | recurse depth+1           |
| 35 | EXEC    | 44   | 1     | 0   | "B"     | {T,T}   | {"AB"}         | used[0]=true              |
| 36 | EXEC    | 45   | 1     | 0   | "BA"    | {T,T}   | {"AB"}         | push 'A'                  |
| 37 | CALL    | →37  | 2     | -   | "BA"    | {T,T}   | {"AB"}         | recurse depth+1           |
| 39 | EXEC    | 39   | 2     | -   | "BA"    | {T,T}   | {"AB","BA"}    | ★ OUTPUT "BA"             |
| 40 | RET     | 40   | 2     | -   | "BA"    | {T,T}   | {"AB","BA"}    | return                    |
| 52 | RET     | 51   | 0     | -   | ""      | {F,F}   | {"AB","BA"}    | final return              |
```

---

13. CALL STACK at step #15 (deepest point for s="AB"):
```
┌──────────────────────────────────────────────────────────────┐
│ FRAME 2 (TOP): perm_helper depth=2 current="AB" i=- line=37  │  ← about to check base case
├──────────────────────────────────────────────────────────────┤
│ FRAME 1:       perm_helper depth=1 current="A"  i=1 line=46  │  ← waiting for return
├──────────────────────────────────────────────────────────────┤
│ FRAME 0:       perm_helper depth=0 current=""   i=0 line=46  │  ← waiting for return
├──────────────────────────────────────────────────────────────┤
│ CALLER:        permutations                          line=68 │  ← waiting for return
└──────────────────────────────────────────────────────────────┘
```

---

14. KEY CONFUSION: FOR LOOP STATES ACROSS STACK FRAMES (at step #19, frame2 just returned)
```
FRAME 0: for loop at i=0 → NOT COMPLETE → still has i=1 pending
FRAME 1: for loop at i=1 → iter i=0 SKIPPED (used[0]=T), iter i=1 DONE
FRAME 2: NO FOR LOOP → base case triggered immediately → 0 iterations

WHY frame1 could NOT run i=0?
→ frame0 set used[0]=T at step #05
→ frame1 entered at step #07 with used={T,F}
→ frame1 loop i=0: !used[0] → !T → F → SKIP
→ frame0 "dirtied" used[0] → frame1 cannot use index 0

WHY frame2 had 0 for loop iterations?
→ frame2 entered at depth=2
→ depth==n → 2==2 → T → base case triggered at line 50
→ never reached line 54 (for loop)
→ immediately output and returned

PATTERN:
frame at depth=0 → picks 1 index → recurses → n-1 indices available in child
frame at depth=1 → picks 1 index → recurses → n-2 indices available in child
frame at depth=n-1 → picks 1 index → recurses → 0 indices available in child
frame at depth=n → base case → no loop → output and return

LOOP ITERATIONS PER FRAME:
frame0: tries n indices → 1 succeeds (used=F) → n-1 fail (used=T)? NO WRONG!
        → at depth=0, used={F,F} → ALL n indices succeed
        → but only 1 at a time → first i=0 succeeds → marks used[0]=T → recurses
        → after return+cleanup → used[0]=F again → i=1 succeeds → marks used[1]=T → recurses
        → so frame0 does n iterations, each with 1 recursive call

frame1: tries n indices → 1 already marked T by parent → n-1 indices available
        → used={T,F} at entry → i=0 skipped → i=1 succeeds

frame2: depth==n → no loop at all

CHILDREN INHERIT PARENT'S DIRTY used[]:
frame0 picks index 0 → used[0]=T
frame1 sees used[0]=T → CANNOT use index 0
frame1 picks index 1 → used[1]=T
frame2 sees used={T,T} → but depth==n → no loop needed
```

---


12. DRAW RECURSION TREE for s="AB" n=2:
```
                    perm(0,"",{F,F})
                    /              \
            pick i=0              pick i=1
              ↓                      ↓
      perm(1,"A",{T,F})      perm(1,"B",{F,T})
           |                        |
      pick i=1                 pick i=0
           ↓                        ↓
   perm(2,"AB",{T,T})      perm(2,"BA",{T,T})
           ↓                        ↓
     OUTPUT "AB"              OUTPUT "BA"
```
→ 2 leaves = 2! = 2 ✓ → fill: how many total nodes? root=1 + level1=_ + level2=_ = _

---

13. DRAW RECURSION TREE for s="ABC" n=3 by hand:
```
                              perm(0,"",{F,F,F})
                     /              |              \
                 i=0               i=1              i=2
                  ↓                 ↓                ↓
          perm(1,"A")        perm(1,"B")      perm(1,"C")
           /      \           /      \          /      \
         i=1     i=2        i=0     i=2       i=0     i=1
          ↓       ↓          ↓       ↓         ↓       ↓
       "AB"     "AC"       "BA"    "BC"      "CA"    "CB"
         |       |           |       |         |       |
        i=2     i=1         i=2     i=0       i=1     i=0
         ↓       ↓           ↓       ↓         ↓       ↓
       "ABC"   "ACB"       "BAC"  "BCA"     "CAB"   "CBA"
```
→ leaves = 6 = 3! ✓ → total nodes = 1 + 3 + 6 + 6 = 16 → fill: function calls for n=4? = 1 + _ + _ + _ + _ = _

---

14. s="AAB" n=3 → naive: 3! = 6 outputs → trace first 3 calls:
```
perm(0,"",{F,F,F})
├─ i=0: s[0]='A' → current="A" → ... → outputs starting with 'A'
├─ i=1: s[1]='A' → current="A" → ... → outputs starting with 'A' (SAME!)
├─ i=2: s[2]='B' → current="B" → ... → outputs starting with 'B'
```
→ i=0 branch: AAB, ABA → i=1 branch: AAB, ABA (DUPLICATES) → i=2 branch: BAA, BAA
→ naive outputs = {AAB, ABA, AAB, ABA, BAA, BAA} = 6 with duplicates
→ unique = {AAB, ABA, BAA} = 3 → formula = 3!/(2!×1!) = 6/2 = 3
→ TRAP: problem says "all permutations" not "unique permutations" → output 6 or 3?

---

15. CALCULATE by hand:
```
n=1: 1! = 1
n=2: 2! = 2
n=3: 3! = 6
n=4: 4! = 24
n=5: 5! = 120
n=6: 6! = 720
n=7: 7! = 5040
n=8: 8! = 40320
n=10: 10! = 3628800
```
→ n=10 → 3.6M outputs → each output = 10 chars → 36MB output → runtime ~ seconds
→ n=12 → 12! = 479001600 → ~479M outputs → program never terminates

---

16. TRACE backtrack for s="AB": iter₁: pick i=0 → used[0]=T → recurse → return → used[0]=F → iter₂: pick i=1 → used[1]=T → recurse → return → used[1]=F → done
```
BEFORE iter₁: used = {F,F}
DURING iter₁: used = {T,F} → recurse
AFTER  iter₁: used = {F,F} ← MUST RESTORE

BEFORE iter₂: used = {F,F}
DURING iter₂: used = {F,T} → recurse
AFTER  iter₂: used = {F,F} ← MUST RESTORE
```
→ TRAP: forgetting `used[i]=false` after return → next iteration sees wrong state

---

17. VERIFY base case: depth==n → output → when? draw:
```
n=3, want output at depth=3:
depth=0 → pick → depth=1 → pick → depth=2 → pick → depth=3 → OUTPUT
         ↑           ↑           ↑              ↑
       1st char   2nd char   3rd char     depth==n ✓
```
→ TRAP: base case depth==n-1 → output at depth=2 → current has only 2 chars → WRONG
→ TRAP: base case depth>n → never triggers → infinite loop

---

18. VERIFY loop bounds:
```
for(i=0; i<n; i++) → i ∈ {0,1,2} for n=3 ✓
for(i=0; i<=n; i++) → i ∈ {0,1,2,3} for n=3 → s[3] = OUT OF BOUNDS ✗
for(i=1; i<=n; i++) → i ∈ {1,2,3} for n=3 → skips s[0] ✗
```

---

19. CALCULATE function call count for s="ABCD" n=4:
```
level 0: 1 call (root)
level 1: 4 calls (pick each of 4)
level 2: 4×3 = 12 calls (3 remaining for each)
level 3: 4×3×2 = 24 calls (2 remaining for each)
level 4: 4×3×2×1 = 24 calls (1 remaining = base case)

total = 1 + 4 + 12 + 24 + 24 = 65 calls
```
→ general formula: Σ(n!/(n-k)!) for k=0..n = Σ P(n,k)

---

20. DRAW memory layout for used[] and current during s="ABC" call#4:
```
0x100: used[0] = 0x01 (true)
0x101: used[1] = 0x01 (true)
0x102: used[2] = 0x01 (true)

0x200: current[0] = 'A' (0x41)
0x201: current[1] = 'B' (0x42)
0x202: current[2] = 'C' (0x43)
0x203: current.size = 3

depth = 3 → depth==n → OUTPUT
```

---

21. FILL: what is current after these operations?
```
current = ""
current.push_back('A') → current = "A"
current.push_back('B') → current = "AB"
current.push_back('C') → current = "ABC"
current.pop_back()     → current = "__"   ← FILL
current.pop_back()     → current = "__"   ← FILL
current.push_back('C') → current = "___"  ← FILL
current.push_back('B') → current = "____" ← FILL
```

---

22. ALGORITHM PATTERN (no solution, structure only):
```
perm(s, n, depth, current, used):
    if _______ :        ← FILL condition
        output current
        return
    for i = ___ to ___ : ← FILL bounds
        if _______ :     ← FILL condition
            used[i] = ___  ← FILL value
            current.push_back(___)  ← FILL what
            perm(s, n, ___, current, used)  ← FILL depth
            _______________  ← FILL: what to undo for current?
            _______________  ← FILL: what to undo for used?
```

---

23. EDGE CASE n=1 s="X": draw full trace:
```
perm(0, "", {F})
└─ i=0: used[0]=T, current="X"
   └─ perm(1, "X", {T})
      └─ depth==n → OUTPUT "X"
```
→ 1! = 1 output ✓

---

24. EDGE CASE n=0 s="": draw:
```
perm(0, "", {})
└─ depth==n → 0==0 ✓ → OUTPUT ""
```
→ 0! = 1 → output empty string? or no output? → clarify: 0!=1 by definition

---

25. CALCULATE unique permutations for duplicate input:
```
s = "AAB" → freq: A=2, B=1
unique = n! / (freq₁! × freq₂! × ...) = 3! / (2! × 1!) = 6/2 = 3

s = "AAAB" → freq: A=3, B=1
unique = 4! / (3! × 1!) = 24/6 = 4

s = "AABB" → freq: A=2, B=2
unique = 4! / (2! × 2!) = 24/4 = 6

s = "AAABB" → freq: A=3, B=2
unique = 5! / (3! × 2!) = 120/(6×2) = 120/12 = 10
```

---

26. TIME/SPACE COMPLEXITY:
```
time: n! outputs × O(n) per output (copy string to result) → O(n × n!)
space: recursion depth = n → O(n) stack
        current string = n chars → O(n)
        used array = n bools → O(n)
        result = n! strings × n chars each → O(n × n!)
```

---

27. VERIFICATION CALCULATIONS:
```
s="AB":   outputs=2   → 2!=2 ✓
s="ABC":  outputs=6   → 3!=6 ✓
s="ABCD": outputs=24  → 4!=24 ✓
s="12345": outputs=120 → 5!=120 ✓
```

---

28. FILL THIS: complete the trace for s="12" n=2
```
| step | depth | current | used[0] | used[1] | action      | output |
|------|-------|---------|---------|---------|-------------|--------|
|  1   |   0   |   ""    |    F    |    F    | pick i=0    |        |
|  2   |   1   |   "1"   |    T    |    F    | pick i=1    |        |
|  3   |   2   |  "12"   |    T    |    T    | OUTPUT      |   12   |
|  4   |   _   |   "_"   |    _    |    _    | ________    |        |
|  5   |   _   |   "_"   |    _    |    _    | ________    |        |
|  6   |   _   |   "_"   |    _    |    _    | ________    |        |
|  7   |   _   |   "_"   |    _    |    _    | ________    |   __   |
```

---

29. DRAW: what does stack look like at deepest point for s="ABCD"?
```
┌─────────────────────────────┐
│ frame 4: depth=4 current="ABCD" ← TOP
├─────────────────────────────┤
│ frame 3: depth=3 current="ABC"
├─────────────────────────────┤
│ frame 2: depth=2 current="AB"
├─────────────────────────────┤
│ frame 1: depth=1 current="A"
├─────────────────────────────┤
│ frame 0: depth=0 current=""     ← BOTTOM
└─────────────────────────────┘
stack depth = 5 frames = n+1
```

---

## FAILURE PREDICTIONS

**F1. index vs character confusion**
```
s="AAB" → s[0]='A' s[1]='A' s[2]='B'
WRONG: track used['A']=true → can't use 'A' again → skips s[1] → only 2 outputs
RIGHT: track used[0]=true used[1]=false → s[1] still available → 6 outputs
```
→ index 0 ≠ index 1 even if s[0]==s[1]

**F2. forgot backtrack used[i]**
```
call 1: i=0 → used[0]=T → recurse → return
        ← FORGOT used[0]=F
call 1: i=1 → used={T,F,F} → recurse into corrupted state
        → branch for i=1 thinks i=0 already used → missing outputs
```

**F3. forgot backtrack current.pop_back()**
```
call depth=2: current="AB" → push 'C' → current="ABC" → recurse → return
              ← FORGOT pop_back()
call depth=2: current="ABC" → push next char → current="ABCD" → depth=2 but len=4 → WRONG
```

**F4. base case off-by-one**
```
WRONG: if(depth == n-1) output → outputs "AB" "AC" "BA" "BC" "CA" "CB" → 6 outputs of length 2 ✗
RIGHT: if(depth == n) output → outputs "ABC" ... → 6 outputs of length 3 ✓
```

**F5. loop bound off-by-one**
```
WRONG: for(i=0; i<=n; i++) → i=3 → s[3] → index out of bounds → undefined behavior
RIGHT: for(i=0; i<n; i++) → i ∈ {0,1,2} → all valid indices
```

**F6. pass string by value**
```
WRONG: void perm(string s, ...) → copy s on each call → n=10 → 10! calls × 10 bytes = 36MB copies
RIGHT: void perm(const string& s, ...) → reference → 0 copies
```

**F7. infinite recursion**
```
WRONG: perm(depth, ...) without depth+1 → depth stays 0 forever → stack overflow
RIGHT: perm(depth+1, ...) → depth increases → eventually depth==n → return
```

**F8. wrong termination check**
```
WRONG: if(i >= n) return → returns from loop, not function → incomplete execution
WRONG: if(current.size() > n) return → never triggers if code is correct
RIGHT: if(depth == n) return after output
```

**F9. duplicate branch entry**
```
s="AAB" → i=0 picks 'A' → i=1 picks 'A' → BOTH valid in naive algo
→ produces duplicate outputs
→ NOT a bug if problem wants all n! permutations
→ IS a bug if problem wants unique permutations only
```

---

## MY MISTAKES DURING IMPLEMENTATION

**M1. loop bound: wrote i < s.size() - 1 then i <= s.size() - 1**
```
line 56: for (int i = 0; i <= s.size() - 1; i++)
         ↓
s="AB" → s.size()=2 → s.size()-1=1 → i<=1 → i∈{0,1} ✓

SHOULD BE: i < n OR i < s.size()
WHY SLOPPY: mixed up < and <= with -1 adjustment
WHAT MISSED: i < n is cleaner than i <= s.size()-1
HOW TO PREVENT: use parameter n directly, avoid s.size()-1 arithmetic
```

**M2. used .at(i) instead of [i]**
```
line 58: used.at(i) = true;
line 62: used.at(i) = false;

.at(i) → bounds checking → slower
[i] → no bounds checking → faster

NOT WRONG: .at(i) works, just slower
WHY: defensive programming habit
VERDICT: acceptable during debugging, change to [i] for performance
```

**M3. confusion about for loop states across stack frames**
```
CONFUSED: "is first stack for loop complete?"
CONFUSED: "why did second stack skip i=0?"
CONFUSED: "why did third stack have 0 loop iterations?"

WHY SLOPPY: not tracking used[] state across frames
WHAT MISSED: parent dirties used[] → child sees dirty state → skips those indices
HOW TO PREVENT: draw used[] state at ENTRY of each frame, not just during
```

**M4. confusion about pop_back necessity**
```
CONFUSED: "why must I undo push_back?"
CONFUSED: "what happens if I don't?"

WHY SLOPPY: not understanding shared reference means shared memory
WHAT MISSED: current is SAME memory in all frames → modifications persist
HOW TO PREVENT: trace memory addresses, not variable names
```

**M5. asked if depth could be global**
```
CONFUSED: "can depth be a global variable?"

WHY SLOPPY: not understanding multiple active frames need different depths
WHAT MISSED: frame0 has depth=0, frame1 has depth=1, SIMULTANEOUSLY
HOW TO PREVENT: draw call stack with local variables for each frame
```

**M6. confused about loop iterating s vs current**
```
CONFUSED: "loop runs on s or current?"

WHY SLOPPY: not clear about source vs destination
WHAT MISSED: s = source pool (fixed), current = destination (grows)
HOW TO PREVENT: label variables clearly: s=SOURCE, current=BUILD_TARGET
```

**M7. proof required for current grow without pop_back**
```
ASKED: "proof that current grows forever"

WHY SLOPPY: did not trace manually, needed spoon-feeding
WHAT MISSED: push_back adds, pop_back removes, no pop_back = accumulation
HOW TO PREVENT: count push_back calls vs pop_back calls, must be equal
```

---

## TRACE OF BUG WITHOUT pop_back (PROOF)

```
step | frame | action            | current state | expected    | VERDICT
-----|-------|-------------------|---------------|-------------|--------
#06  | 0     | push_back('A')    | "A"           | "A"         | ✓
#14  | 1     | push_back('B')    | "AB"          | "AB"        | ✓
#17  | 2     | OUTPUT            | "AB"          | "AB"        | ✓
#19  | 1     | (no pop_back)     | "AB"          | "A"         | ✗ DIRTY
#24  | 0     | (no pop_back)     | "AB"          | ""          | ✗ DIRTY
#30  | 0     | push_back('B')    | "ABB"         | "B"         | ✗ GARBAGE
#35  | 1     | push_back('A')    | "ABBA"        | "BA"        | ✗ GARBAGE
#38  | 2     | OUTPUT            | "ABBA"        | "BA"        | ✗ WRONG OUTPUT
```

```
push_back count: 4
pop_back count: 0
imbalance: 4 - 0 = 4 → current.size() grows by 4 instead of oscillating 0→1→2→1→0→1→2→...
```

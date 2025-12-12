# M(i,j)=1 if i=j, M(i,j)=2 if j=i+1, M(i,j)=M(i+1,j-1)×M(i+1,j)×M(i,j-1) if j>i+1

```
n=5 → M(1,5)=?
     j=1  j=2  j=3  j=4  j=5
i=1   1    2    ?    ?    ?
i=2   ×    1    2    ?    ?
i=3   ×    ×    1    2    ?
i=4   ×    ×    ×    1    2
i=5   ×    ×    ×    ×    1
```

01. n=5 → i∈{1,2,3,4,5}, j∈{1,2,3,4,5}, 1≤i≤j≤n → upper triangle → cells={(1,1),(1,2),(1,3),(1,4),(1,5),(2,2),(2,3),(2,4),(2,5),(3,3),(3,4),(3,5),(4,4),(4,5),(5,5)} → count=15=n(n+1)/2=5×6/2 ✓
02. L=j-i+1 → length of range → L=1 means i=j → M(i,i)=1 (axiom) → L=2 means j=i+1 → M(i,i+1)=2 (axiom) → L≥3 means j>i+1 → M(i,j)=M(i+1,j-1)×M(i+1,j)×M(i,j-1) (recurrence)
03. M(1,3) needs M(2,2),M(2,3),M(1,2) → M(2,2)=1 (L=1), M(2,3)=2 (L=2), M(1,2)=2 (L=2) → all L<3 → dependencies satisfied ✓ → M(1,3)=1×2×2=4
04. M(2,4) needs M(3,3),M(3,4),M(2,3) → M(3,3)=1 (L=1), M(3,4)=2 (L=2), M(2,3)=2 (L=2) → all L<3 → M(2,4)=1×2×2=4
05. M(3,5) needs M(4,4),M(4,5),M(3,4) → M(4,4)=1 (L=1), M(4,5)=2 (L=2), M(3,4)=2 (L=2) → all L<3 → M(3,5)=1×2×2=4
06. M(1,4) needs M(2,3),M(2,4),M(1,3) → M(2,3)=2 (L=2), M(2,4)=4 (L=3, step 04), M(1,3)=4 (L=3, step 03) → all L<4 → M(1,4)=2×4×4=32
07. M(2,5) needs M(3,4),M(3,5),M(2,4) → M(3,4)=2 (L=2), M(3,5)=4 (L=3, step 05), M(2,4)=4 (L=3, step 04) → all L<4 → M(2,5)=2×4×4=32
08. M(1,5) needs M(2,4),M(2,5),M(1,4) → M(2,4)=4 (L=3, step 04), M(2,5)=32 (L=4, step 07), M(1,4)=32 (L=4, step 06) → all L<5 → M(1,5)=4×32×32=4096

```
     j=1  j=2  j=3  j=4  j=5
i=1   1    2    4   32  4096    ← M(1,5)=4096
i=2   ×    1    2    4   32
i=3   ×    ×    1    2    4
i=4   ×    ×    ×    1    2
i=5   ×    ×    ×    ×    1
```

09. dependency M(i,j) → {M(i+1,j-1), M(i+1,j), M(i,j-1)} → M(i+1,j-1) is row i+1, col j-1 → below-left diagonal → M(i+1,j) is row i+1, col j → directly below → M(i,j-1) is row i, col j-1 → directly left → fill order: diagonal L=1 first, then L=2, then L=3, ... → bottom-up by length ✓
10. recursive M(1,5) → calls {M(2,4), M(2,5), M(1,4)} → M(2,4) calls {M(3,3), M(3,4), M(2,3)} → M(2,5) calls {M(3,4), M(3,5), M(2,4)} → M(1,4) calls {M(2,3), M(2,4), M(1,3)} → M(2,4) called from M(1,5) AND from M(2,5) AND from M(1,4) → 3× redundant → M(2,3) called from M(2,4) AND from M(1,4) → 2× redundant
11. count calls T(L) for length L → T(1)=1, T(2)=1 → T(3)=T(1)+T(2)+T(2)+1=1+1+1+1=4 → T(4)=T(2)+T(3)+T(3)+1=1+4+4+1=10 → T(5)=T(3)+T(4)+T(4)+1=4+10+10+1=25 → T(6)=T(4)+T(5)+T(5)+1=10+25+25+1=61 → growth ≈ 2.5× per level → exponential ✗
12. unique cells = n(n+1)/2 = 15 for n=5 → recursive calls = 25 for L=5 alone → 25>15 → overlap ratio = calls/unique = 25/15 ≈ 1.67 → n=10 → unique=55 → calls≈3^5≈243 for top cell → overlap worsens → memoization needed ✓

F1. fill M(1,4) before M(2,4) → M(1,4)=M(2,3)×M(2,4)×M(1,3) → M(2,4)=? undefined → wrong order → must fill L=3 before L=4 ✗
F2. loop i=1 to n, j=i to n → i=1,j=3: M(1,3)=M(2,2)×M(2,3)×M(1,2)=1×2×2=4 ✓ → i=1,j=4: M(1,4)=M(2,3)×M(2,4)×M(1,3)=2×?×4 → M(2,4) not yet computed (i=2,j=4 comes later) ✗ → row-major order fails
F3. loop j=1 to n, i=1 to j → j=3: i=1 M(1,3)=1×2×2=4 ✓, i=2 M(2,3)=2 (base) ✓, i=3 M(3,3)=1 (base) ✓ → j=4: i=1 M(1,4)=2×M(2,4)×4 → M(2,4) not yet computed (i=2 at j=4 comes after i=1) ✗ → column-major fails
F4. loop L=1 to n, i=1 to n-L+1, j=i+L-1 → L=3: i=1,j=3 M(1,3)=1×2×2=4 → i=2,j=4 M(2,4)=1×2×2=4 → i=3,j=5 M(3,5)=1×2×2=4 → L=4: i=1,j=4 M(1,4)=2×4×4=32 → all dependencies ready ✓ → length-major order works ✓

13. time: L from 2 to n → (n-1) lengths → each L: (n-L+1) cells → each cell: 2 multiplications O(1) → total cells = Σ(n-L+1) for L=2..n = (n-1)+(n-2)+...+1 = (n-1)n/2 = O(n²) → time O(n²) ✓
14. space: table M[n+1][n+1] → (n+1)² entries × 8 bytes (long long) → n=5 → 36×8=288 bytes → n=100 → 10201×8=81608 bytes ≈ 80KB → O(n²) space ✓
15. space optimization: M(i,j) depends on M(i+1,j-1) (L-2), M(i+1,j) (L-1), M(i,j-1) (L-1) → need only diagonals L-2 and L-1 to compute L → store 3 arrays of size n → 3n entries → O(n) space possible ✓

16. n=6 → M(1,6)=M(2,5)×M(2,6)×M(1,5) → M(2,5)=32 (step 07 pattern), M(1,5)=4096 (step 08) → need M(2,6)=M(3,5)×M(3,6)×M(2,5) → M(3,5)=4 (step 05), M(2,5)=32 → need M(3,6)=M(4,5)×M(4,6)×M(3,5) → M(4,5)=2 (base), M(3,5)=4 → need M(4,6)=M(5,5)×M(5,6)×M(4,5)=1×2×2=4 → M(3,6)=2×4×4=32 → M(2,6)=4×32×32=4096 → M(1,6)=32×4096×4096=536870912=2²⁹
17. n=7 → M(1,7) depends on M(2,6)=4096, M(2,7), M(1,6)=2²⁹ → M(2,7) depends on M(3,6)=32, M(3,7), M(2,6)=4096 → ... → pattern: M(1,n) ≈ 2^(2^(n-2)) → n=7 → 2^(2^5)=2^32 → n=8 → 2^64 → overflows long long (2⁶³-1) ✗ → use __int128 or bigint for n>6

18. loop structure: for L=2 to n: for i=1 to n-L+1: j=i+L-1, M[i][j]=M[i+1][j-1]*M[i+1][j]*M[i][j-1] → L=2,i=1: j=2, M[1][2]=2 (base, skip recurrence) ✗ → L=2 is base case → loop L from 3 to n only, pre-fill L=1 and L=2 ✓
19. edge n=1 → only M(1,1)=1 → no recurrence needed → return 1 directly ✓
20. edge n=2 → M(1,1)=1, M(2,2)=1, M(1,2)=2 → target M(1,2)=2 → no recurrence needed → return 2 directly ✓

```
recursive tree M(1,5):
M(1,5)
├── M(2,4) ─────────────────┐
│   ├── M(3,3)=1            │
│   ├── M(3,4)=2            │
│   └── M(2,3)=2            │
├── M(2,5)                  │
│   ├── M(3,4)=2  ←─────────┼── duplicate
│   ├── M(3,5)              │
│   │   ├── M(4,4)=1        │
│   │   ├── M(4,5)=2        │
│   │   └── M(3,4)=2 ←──────┼── duplicate
│   └── M(2,4) ←────────────┘── duplicate (entire subtree)
└── M(1,4)
    ├── M(2,3)=2  ←── duplicate
    ├── M(2,4) ←────── duplicate (entire subtree)
    └── M(1,3)
        ├── M(2,2)=1
        ├── M(2,3)=2 ←── duplicate
        └── M(1,2)=2
```

21. count M(2,4) occurrences in tree: once from M(1,5), once from M(2,5), once from M(1,4) → 3× total → each M(2,4) spawns 3 more calls → 3×3=9 redundant calls from M(2,4) alone → without memo → exponential blowup ✓
22. count M(2,3) occurrences: from M(2,4)×3, from M(1,4)×1 → 4× total → each is base case (L=2) → 4 redundant lookups → with memo table → 1 compute + 3 lookups O(1) ✓

complexity: time O(n²), space O(n²), reducible to O(n) with rolling diagonals

---

## MISTAKES LOG

E1. line 40 → `for(int i=1; i<=n; i++) M[i][i+1]=2` → i=n → M[n][n+1] → index n+1 exceeds size n+1 → out of bounds ✗
    → sloppy: copied L=1 loop bounds without thinking
    → missed: j=i+1 must satisfy j≤n → i+1≤n → i≤n-1
    → fix: `i<=n-1` or `i<n`
    → prevent: trace boundary i=n → j=n+1 → j>n ✗ → catch before run

E2. line 46-51 → wrote `for(int j=i; j<=i+L-1; j++)` → j is loop ✗
    → sloppy: assumed j needs iteration like i
    → missed: for fixed L,i → j = i+L-1 is ONE value, not range
    → fix: `int j = i+L-1;` single assignment
    → prevent: count cells per (L,i) → exactly 1 → no loop needed

E3. confusion → "why L=3" → "what is L" → "why j-i+1"
    → sloppy: accepted L variable without derivation
    → missed: L = j-i+1 = count of integers in [i,j] = subproblem size
    → prevent: trace M[1][3] → i=1,j=3 → count{1,2,3}=3 → L=3 ✓

E4. confusion → "why n-L+1"
    → sloppy: accepted loop bound without checking
    → missed: j=i+L-1 must satisfy j≤n → i≤n-L+1
    → prevent: trace L=3,n=5 → i=4 → j=6>5 ✗ → i must stop at 3=5-3+1

E5. confusion → "why fill diagonal with 1"
    → sloppy: not connecting code to problem axiom
    → missed: problem says M(i,j)=1 if i=j → diagonal cells
    → prevent: map each code line to problem statement clause

E6. confusion → "why care about dependencies"
    → sloppy: thought any fill order works
    → missed: M[1][4] needs M[2][4] → must fill M[2][4] first → order matters
    → prevent: trace M[1][4]=M[2][3]×M[2][4]×M[1][3] → if M[2][4]=0 → wrong answer

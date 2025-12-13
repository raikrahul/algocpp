[ SYSTEM STATE: MEMORY INITIALIZATION ]
START_ADDR | LEFT(0) OFFSET | RIGHT(1) OFFSET | VALUE_PTR OFFSET
0x100      | +0x00          | +0x04           | +0x08
BLOCK_SIZE | 0x0C (12 Bytes)| HEAP_PTR        | 0x100
ROOT_ADDR  | 0x100          |

1. Heap_Ptr 0x100 → Alloc(Root) → Memory[0x100...0x10B] ← {0x00, 0x00, 0x00, ...}
2. Root.Left = Memory[0x100] = 0x000 (NULL)
3. Root.Right = Memory[0x104] = 0x000 (NULL)
4. Root.Value = Memory[0x108] = ∅
5. Heap_Ptr update: 0x100 + 0x0C = 0x10C

[ MEMORY MAP STATE 0 ]
ADDR   | LEFT (0x00) | RIGHT (0x04) | VALUE (0x08)
-------|-------------|--------------|-------------
0x100  | 0x000       | 0x000        | ∅
Next   | 0x10C       |              |

6. INPUT: add(0x80000000, 1, "eth") → Addr=0x80000000=10000000...₂ → Len=1 → Val="eth"
7. Loop: depth=0 to Len-1 (0)
8. Iter₀ (Bit 31): Pos=31-0=31 → (0x80000000 >>> 31) = 0x01 → 0x01 & 1 = 1
9. Bit=1 → Require Right child of 0x100 → Check Memory[0x104]=0x000 (NULL)
10. Alloc: Heap_Ptr=0x10C → Write Memory[0x104] ← 0x10C → Link 0x100→0x10C
11. Memory[0x10C...0x117] ← 0 → Heap_Ptr=0x10C+0x0C=0x118
12. Move: Current 0x100 → 0x10C
13. Termination: depth(0)==Len-1(0) → Write Value → Memory[0x10C+8] ← "eth"

[ MEMORY MAP STATE 1 ]
ADDR   | LEFT (0)    | RIGHT (1)    | VALUE      | PATH
-------|-------------|--------------|------------|-----
0x100  | 0x000       | 0x10C        | ∅          | Root
0x10C  | 0x000       | 0x000        | "eth"      | 1
Next   | 0x118       |              |            |

14. INPUT: add(0xC0000000, 2, "ir") → Addr=0xC0000000=11000000...₂ → Len=2 → Val="ir"
15. Iter₀ (Bit 31): (0xC0000000 >>> 31) & 1 = 1 → Current=0x100 → Memory[0x104]=0x10C ≠ NULL ✓
16. Move: Current 0x100 → 0x10C
17. Iter₁ (Bit 30): (0xC0000000 >>> 30) & 1 = 1 → Check: 0xC=1100 → bit₃₀=1 ✓
18. Current=0x10C → Memory[0x10C+4]=0x000 (NULL) → Alloc 0x118
19. Write Memory[0x10C+4] ← 0x118 → Init 0x118 ← 0 → Heap_Ptr=0x124
20. Move: Current 0x10C → 0x118
21. Termination: depth(1)==Len-1(1) → Write Value → Memory[0x118+8] ← "ir"

[ MEMORY MAP STATE 2 ]
ADDR   | LEFT  | RIGHT | VALUE | PATH
0x100  | 0x000 | 0x10C | ∅     | Root
0x10C  | 0x000 | 0x118 | "eth" | 1
0x118  | 0x000 | 0x000 | "ir"  | 11
Next   | 0x124 |       |       |

22. INPUT: add(0x80000000, 2, "usb") → Addr=0x80000000=10000000...₂ → Len=2 → Val="usb"
23. Iter₀ (Bit 31): 1 → 0x100→Right=0x10C → Move→0x10C
24. Iter₁ (Bit 30): (0x80000000 >>> 30) & 1 → 0x8=1000 → bit₃₀=0
25. Bit=0 → Require Left of 0x10C → Memory[0x10C+0]=0x000 (NULL)
26. Alloc 0x124 → Write Memory[0x10C+0] ← 0x124 → Heap_Ptr=0x130
27. Move: Current → 0x124
28. Termination → Memory[0x124+8] ← "usb"

[ MEMORY MAP STATE 3 ]
ADDR   | LEFT  | RIGHT | VALUE | BINARY
0x100  | 0x0   | 0x10C | ∅     |
0x10C  | 0x124 | 0x118 | "eth" | 1
0x118  | 0x0   | 0x0   | "ir"  | 11
0x124  | 0x0   | 0x0   | "usb" | 10
Next   | 0x130 |       |       |

29. INPUT: add(0xB0000000, 4, "ppp") → Addr=0xB0000000=10110000...₂ → Len=4 → Val="ppp"
30. Trace₀ (1): 0x100→Right=0x10C (Found)
31. Trace₁ (0): 0x10C→Left=0x124 (Found, "usb")
32. Trace₂ (1): (0xB0000000 >>> 29) & 1 → 0xB=1011 → bit₂₉=1 → 10[1]1
33. Check 0x124→Right(+4)=0x000 → Alloc 0x130 → Link 0x124.Right←0x130 → Value 0x130←∅
34. Trace₃ (1): (0xB0000000 >>> 28) & 1 → bit₂₈=1 → 101[1]
35. Check 0x130→Right(+4)=0x000 → Alloc 0x13C → Link 0x130.Right←0x13C → Heap←0x148
36. Termination → Memory[0x13C+8] ← "ppp"

[ MEMORY MAP STATE 4 ]
[0x100: ∅]
         | R (1)
     [0x10C: "eth"]
      / L(0)      \ R(1)
[0x124: "usb"]   [0x118: "ir"]
      \ R(1)
    [0x130: ∅]
         \ R(1)
       [0x13C: "ppp"]

37. INPUT: add(0x00000000, 3, "wifi1") → Addr=0x00000000=00000000...₂ → Len=3 → Val="wifi1"
38. Trace₀ (0): 0x100→Left=0x000 → Alloc 0x148 → Link 0x100.Left←0x148 → Heap←0x154
39. Trace₁ (0): 0x148→Left=0x000 → Alloc 0x154 → Link 0x148.Left←0x154 → Heap←0x160
40. Trace₂ (0): 0x154→Left=0x000 → Alloc 0x160 → Link 0x154.Left←0x160 → Heap←0x16C
41. Termination → Memory[0x160+8] ← "wifi1"

42. INPUT: add(0x20000000, 3, "wifi2") → Addr=0x20000000=00100000...₂ → Len=3 → Val="wifi2"
43. Trace₀ (0): 0x100→Left=0x148 (Found)
44. Trace₁ (0): 0x148→Left=0x154 (Found)
45. Trace₂ (1): (0x20000000 >>> 29) & 1 → 0x2=0010 → bit₂₉=1 → 00[1]
46. Check 0x154→Right(+4)=0x000 → Alloc 0x16C → Link 0x154.Right←0x16C → Heap←0x178
47. Termination → Memory[0x16C+8] ← "wifi2"

[ MEMORY MAP STATE 5 - FINAL ]
ADDR   | LEFT  | RIGHT | VALUE   | BINARY
0x100  | 0x148 | 0x10C | ∅       | Root
0x10C  | 0x124 | 0x118 | "eth"   | 1
0x118  | 0x000 | 0x000 | "ir"    | 11
0x124  | 0x000 | 0x130 | "usb"   | 10
0x130  | 0x000 | 0x13C | ∅       | 101
0x13C  | 0x000 | 0x000 | "ppp"   | 1011
0x148  | 0x154 | 0x000 | ∅       | 0
0x154  | 0x160 | 0x16C | ∅       | 00
0x160  | 0x000 | 0x000 | "wifi1" | 000
0x16C  | 0x000 | 0x000 | "wifi2" | 001
Next   | 0x178 |       |         |

48. QUERY: route(0xAF000000) → Addr=10101111...₂ → Best_Match=∅
49. Pass₀: Bit=(0xAF000000>>>31)&1=1 → 0x100→Right=0x10C → 0x10C.Value="eth"≠∅ → Best="eth"
50. Pass₁: Bit=(0xAF000000>>>30)&1=0 → 0x10C→Left=0x124 → 0x124.Value="usb"≠∅ → Best="usb"
51. Pass₂: Bit=(0xAF000000>>>29)&1=1 → 0x124→Right=0x130 → 0x130.Value=∅ → Best="usb"
52. Pass₃: Bit=(0xAF000000>>>28)&1=0 → 0x130→Left=0x000 (NULL) → BREAK
53. Return Best_Match="usb" ✓

54. QUERY: route(0x40000000) → Addr=01000000...₂ → Best_Match=∅
55. Pass₀: Bit=(0x40000000>>>31)&1=0 → 0x4=0100 → MSB=0
56. Check 0x100→Left=0x148 → 0x148.Value=∅ → Best=∅
57. Pass₁: Bit=(0x40000000>>>30)&1=1 → 0x148→Right=0x000 (NULL) → BREAK
58. Best_Match=∅ → THROW ✗

59. QUERY: route(0xB0000000) → Addr=10110000...₂ → Best_Match=∅
60. Pass₀: 1 → 0x10C → Best="eth"
61. Pass₁: 0 → 0x124 → Best="usb"
62. Pass₂: 1 → 0x130 → Value=∅ → Best="usb"
63. Pass₃: 1 → 0x13C → Best="ppp"
64. Pass₄: 0 → 0x13C→Left=0x000 → BREAK
65. Return "ppp" ✓

66. QUERY: route(0xC0000000) → Addr=11000000...₂ → Best_Match=∅
67. Pass₀: 1 → 0x10C → Best="eth"
68. Pass₁: 1 → 0x118 → Best="ir"
69. Pass₂: 0 → 0x118→Left=0x000 → BREAK
70. Return "ir" ✓

71. USER EXERCISE 1: route(0x00000000) → trace passes → expected="wifi1"
72. USER EXERCISE 2: route(0x10000000)=00010000...₂ → trace → expected="wifi1"
73. USER EXERCISE 3: add(0xE0000000, 3, "new")=111₂ → draw Memory Map State 6

74. FORMULA: Bit_i = (Address >>> (31-i)) & 1
75. FORMULA: Ptr_next = Memory[Ptr_curr + (Bit_i × 4)]
76. FORMULA: Val_update = (Memory[Ptr_next + 8] ≠ ∅) → Best ← Ptr_next.Val

77. ALGORITHM add(addr, n, val): cur=root → for i=0 to n-1: bit=(addr>>>(31-i))&1 → offset=bit×4 → if Memory[cur+offset]=0x000: alloc → cur=Memory[cur+offset] → Memory[cur+8]=val

78. ALGORITHM route(addr): cur=root, best="" → for i=0 to 31: if cur=0x000: break → if Memory[cur+8]≠∅: best=Memory[cur+8] → bit=(addr>>>(31-i))&1 → cur=Memory[cur+bit×4] → if best="": throw → return best

F1. n=0 → loop 0 to -1 → no iterations → cur=root → Memory[root+8]=val → root gets value → undefined? → n≥1 required
F2. n>32 → shift (31-i) goes negative for i>31 → undefined behavior → n≤32 required
F3. signed shift vs unsigned → (int)0x80000000=-2147483648 → >> propagates sign bit → use >>> or (unsigned int) cast
F4. check Value AFTER move vs BEFORE move → if check after: miss current node value → check BEFORE moving
F5. child[0]/child[1] confusion → Left=+0x00, Right=+0x04 → bit=0→Left, bit=1→Right
F6. root not initialized → root=nullptr → first Memory[nullptr+offset] → segfault
F7. best="" but no throw → returns "" instead of exception → must check best≠""
F8. memory leak → destructor must traverse and delete all nodes recursively

79. TIME: add O(n) where n=bits, max 32 → O(32)=O(1)
80. TIME: route O(32)=O(1)
81. SPACE: O(nodes) → max nodes=2^33-1 → practical O(prefixes × avg_depth)
82. MEMORY PER NODE: 12 bytes (Left+Right+Value_ptr) → 1000 prefixes × 32 depth × 12 = 384KB worst case

[ USER ERRORS DURING IMPLEMENTATION ]

E1. Line 36 (original): `int bit = (address >> (31 - i) & 1 );`
    WRONG: `(31 - i) & 1` evaluates first → shift by 1 or 0
    CORRECT: `(address >> (31 - i)) & 1`
    MISSED: operator precedence `>>` vs `&`
    PREVENT: parenthesize shift expression completely

E2. Line 66: `Node* cur = root` ← missing semicolon
    WRONG: syntax error → compilation fails
    CORRECT: `Node* cur = root;`
    MISSED: statement terminator
    PREVENT: compile after each line

E3. Line 73: `int bit = (address >> (31 - i))` ← missing `& 1`
    WRONG: bit = 0x00000001 or 0x00000002 → not 0 or 1
    CORRECT: `(address >> (31 - i)) & 1`
    MISSED: mask to extract single bit
    PREVENT: copy from add() which was correct

E4. Line 95: missing throw logic
    WRONG: returns "" when no match → Test 1 fails
    CORRECT: `if (best.empty()) throw std::runtime_error("...")`
    MISSED: exception requirement from problem statement
    PREVENT: read problem spec: "exception is thrown"

E5. Lines 90-92: duplicate FILL comments left in code
    WRONG: dead comments after implementation
    CORRECT: remove after filling
    MISSED: cleanup
    PREVENT: delete comment after implementing

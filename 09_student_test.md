## Problem 09: Student Test - Pure Symbolic Axiomatic Derivation

**GIVEN:**
K = 10
T = {10, 2, 2, 2}
n = 4
Sum(T) = 10+2+2+2 = 16
16 > 10 ✓

**STRATEGY A: "Pick Longest First"**

Step 0:
T = {10, 2, 2, 2}
→ Sort Descending
→ {10, 2, 2, 2}

Step 1:
remaining = 10
questions = []
count = 0

Step 2:
i = 0
T[0] = 10
10 ≤ 10 ✓
→ pick 10
→ remaining = 10 - 10 = 0
→ questions = [10]
→ count = 1

Step 3:
i = 1
T[1] = 2
2 ≤ 0 ✗
→ skip

Step 4:
i = 2
T[2] = 2
2 ≤ 0 ✗
→ skip

Step 5:
i = 3
T[3] = 2
2 ≤ 0 ✗
→ skip

**OUTPUT A:**
count = 1

---

**ALTERNATIVE: "Pick Shortest First"**

Step 0:
T = {10, 2, 2, 2}
→ Sort Ascending
→ {2, 2, 2, 10}

Step 1:
remaining = 10
questions = []
count = 0

Step 2:
i = 0
T[0] = 2
2 ≤ 10 ✓
→ pick 2
→ remaining = 10 - 2 = 8
→ questions = [2]
→ count = 1

Step 3:
i = 1
T[1] = 2
2 ≤ 8 ✓
→ pick 2
→ remaining = 8 - 2 = 6
→ questions = [2, 2]
→ count = 2

Step 4:
i = 2
T[2] = 2
2 ≤ 6 ✓
→ pick 2
→ remaining = 6 - 2 = 4
→ questions = [2, 2, 2]
→ count = 3

Step 5:
i = 3
T[3] = 10
10 ≤ 4 ✗
→ skip

**OUTPUT ALTERNATIVE:**
count = 3

**COMPARISON:**
1 < 3 ✓
∴ Strategy A ✗

---

**GIVEN:**
K = 10
T = {3, 8}
n = 2
Sum(T) = 3+8 = 11
11 > 10 ✓

**STRATEGY B: "Pick Shortest First for Max Time"**

Step 0:
T = {3, 8}
→ Sort Ascending
→ {3, 8}

Step 1:
remaining = 10
time_used = 0

Step 2:
i = 0
T[0] = 3
3 ≤ 10 ✓
→ pick 3
→ remaining = 10 - 3 = 7
→ time_used = 0 + 3 = 3

Step 3:
i = 1
T[1] = 8
8 ≤ 7 ✗
→ skip

**OUTPUT B:**
time_used = 3

---

**ALTERNATIVE: "Pick {8}"**

Step 0:
T = {8}

Step 1:
remaining = 10
time_used = 0

Step 2:
8 ≤ 10 ✓
→ pick 8
→ remaining = 10 - 8 = 2
→ time_used = 0 + 8 = 8

**OUTPUT ALTERNATIVE:**
time_used = 8

**COMPARISON:**
3 < 8 ✓
∴ Strategy B ✗

---

**DERIVATION:**

K = 10
T = {3, 8}

All subsets:
{} → sum = 0
{3} → sum = 3
{8} → sum = 8
{3, 8} → sum = 11

Constraint: sum ≤ 10
{} → 0 ≤ 10 ✓
{3} → 3 ≤ 10 ✓
{8} → 8 ≤ 10 ✓
{3, 8} → 11 ≤ 10 ✗

Valid subsets: {}, {3}, {8}
Sum values: 0, 3, 8
max(0, 3, 8) = 8
∴ Optimal = 8

Strategy B → 3
3 ≠ 8
∴ Strategy B ✗

---

**DP TRACE:**

K = 10
T = {3, 8}
dp[0..10] = boolean array

Init:
dp[0] = true
dp[1] = false
dp[2] = false
dp[3] = false
dp[4] = false
dp[5] = false
dp[6] = false
dp[7] = false
dp[8] = false
dp[9] = false
dp[10] = false

Process T[0] = 3:
j = 10: dp[10] = dp[10] OR dp[10-3] = false OR dp[7] = false OR false = false
j = 9: dp[9] = dp[9] OR dp[9-3] = false OR dp[6] = false OR false = false
j = 8: dp[8] = dp[8] OR dp[8-3] = false OR dp[5] = false OR false = false
j = 7: dp[7] = dp[7] OR dp[7-3] = false OR dp[4] = false OR false = false
j = 6: dp[6] = dp[6] OR dp[6-3] = false OR dp[3] = false OR false = false
j = 5: dp[5] = dp[5] OR dp[5-3] = false OR dp[2] = false OR false = false
j = 4: dp[4] = dp[4] OR dp[4-3] = false OR dp[1] = false OR false = false
j = 3: dp[3] = dp[3] OR dp[3-3] = false OR dp[0] = false OR true = true

State after T[0]:
dp[0] = true
dp[3] = true
others = false

Process T[1] = 8:
j = 10: dp[10] = dp[10] OR dp[10-8] = false OR dp[2] = false OR false = false
j = 9: dp[9] = dp[9] OR dp[9-8] = false OR dp[1] = false OR false = false
j = 8: dp[8] = dp[8] OR dp[8-8] = false OR dp[0] = false OR true = true

State after T[1]:
dp[0] = true
dp[3] = true
dp[8] = true
others = false

Find max j where dp[j] = true:
j = 10: false
j = 9: false
j = 8: true ✓

∴ max_time = 8

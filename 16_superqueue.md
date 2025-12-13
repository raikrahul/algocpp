PROBLEM: Queue with O(1) enqueue, O(1) dequeue, O(1) findmin.

01. DRAW Q=[], then ENQUEUE(10), ENQUEUE(5), ENQUEUE(20), write Q after each operation, this builds on nothing, you start from empty.

02. Using Q from step 01, call findmin(), what value do you return? scan Q left to right, find smallest, write the count of comparisons, this builds on step 01.

03. Count from step 02 is ___, if Q has N elements, count is ___, O(___), constraint says O(1), is O(___) = O(1)? ✓ or ✗? this builds on step 02.

04. TRAP: you will try to store min in a variable, DRAW Q=[10,5,20], min_var=5, now DEQUEUE(), which element leaves? ___, Q becomes [___,___], is min_var still correct? ✓ or ✗? this builds on step 01.

05. TRAP: using Q=[5,20] from step 04, DEQUEUE() again, which element leaves? ___, Q becomes [___], min_var was 5, is min_var still correct? ✓ or ✗? what is actual min now? ___, how do you know actual min without scanning? this builds on step 04.

06. FAILURE: step 05 shows min_var becomes stale when ___ leaves, you need to know ___ min, but you only stored ___ min, ∴ single variable fails, write: "F1: ___________".

07. TRAP: you will try heap, heap.push(x) costs O(___) for N elements, constraint says O(1), O(log N) = O(1)? ✓ or ✗? write: "F2: ___________".

08. OBSERVATION: DRAW timeline, T₁: 10 enters, T₂: 5 enters, T₃: 20 enters, elements leave in order ___, ___, ___ because FIFO.

09. QUESTION: between T₂ and when 10 leaves, both 10 and 5 are present, who is min? ___, after 10 leaves, is 10 still in Q? ✓ or ✗? ∴ can 10 ever be min after T₂? ✓ or ✗? this builds on step 08.

10. QUESTION: 10 is smaller/larger than 5? ___, 10 arrived before/after 5? ___, 10 leaves before/after 5? ___, ∴ while both present ___ wins, after 10 leaves ___ is gone, ∴ 10 is useful/useless after T₂? this builds on step 09.

11. GENERALIZE: element X is useless if element Y exists where Y < X ∧ Y arrived ___ X, fill the blank: before/after, this builds on step 10.

12. CALCULATE: input [10, 5, 20, 3], which elements are useless at the end? apply rule from step 11 to each pair, show work.
```
10 vs 5: 5<10 ∧ 5 arrived after 10 → 10 useless? ___
10 vs 20: 20<10? ___ → skip
10 vs 3: 3<10 ∧ 3 arrived after 10 → 10 useless? ___
5 vs 20: 20<5? ___ → skip
5 vs 3: 3<5 ∧ 3 arrived after 5 → 5 useless? ___
20 vs 3: 3<20 ∧ 3 arrived after 20 → 20 useless? ___
```
this builds on step 11.

13. RESULT: from step 12, useless elements are {___,___,___}, useful elements are {___}, min = ___.

14. OBSERVATION: if we only keep useful elements, we have set {___} from step 13, size = ___, is this smaller than original size 4? ✓ or ✗?

15. QUESTION: we need a structure to hold useful elements, when new element x arrives, we must remove all useless elements, which elements become useless when x arrives? elements that are __less_ than x and arrived __after__ x, this builds on step 11.

16. CALCULATE: D=[5,20] (useful elements so far), x=3 arrives, 5>3? _yes__, 5 arrived __before__ 3? ___, ∴ 5 useless? yes___, 20>3? _yes__, 20 arrived _before_before__ 3? __yes_, ∴ 20 useless? __yes_, after removing useless, D=[___], add 3, D=[_3__].

17. QUESTION: in step 16, we checked D=[5,20] from right to left or left to right? ___,right to left we removed from which end? _left __, ∴ D is stack/queue/deque? this builds on step 16.q

18. QUESTION: after step 16, D=[3], min is at front/back? ___, ∴ findmin() returns D.___().

19. CALCULATE: D=[5,20], new x=25 arrives, 20>25? ✓ or ✗? ∴ remove 20? ✓ or ✗? 5>25? ✓ or ✗? ∴ remove 5? ✓ or ✗? ∴ D becomes [5,20,___], this builds on step 16 pattern.

20. PROPERTY: after each insert, is D sorted ascending/descending? ___, verify with D from step 16 and step 19.

21. DEQUEUE QUESTION: Q=[10,5,20,3], D=[3], DEQUEUE removes 10, is 10 in D? ✓ or ✗? do we modify D? ✓ or ✗? this builds on step 12-13 (10 was useless).

22. DEQUEUE QUESTION: Q=[3], D=[3], DEQUEUE removes 3, is 3 in D? ✓ or ✗? 3 == D.front()? ✓ or ✗? ∴ we must ___ from D.

23. DEQUEUE RULE: if element leaving Q == D.front() then D.___(). fill blank.

24. WRITE CODE: based on step 17-18, what container type for D? std::___<int>, this builds on step 17.

25. WRITE CODE: based on step 15-16, enqueue(x) loop condition is: while (!D.empty() ∧ x ___ D.back()) D.pop___(); then D.push___(x); fill blanks using step 16.

26. WRITE CODE: based on step 23, dequeue() has: if (Q.front() == D.front()) D.pop___(); Q.pop(); fill blank.

27. WRITE CODE: based on step 18, findmin() returns D.___();

28. EDGE: Q=[], D=[], findmin() calls D.front(), D is empty, what happens? ___, how to prevent? add check: if (___) throw/return sentinel. 

29. DUPLICATE TEST: input [2,2], step by step apply rule from step 25, is condition 2 < 2? ✓ or ✗? ∴ second 2 is pushed/not pushed? verify D=[___,___] or D=[___].

30. WRONG OPERATOR TEST: if you used <= instead of <, input [2,2], condition 2 <= 2? ✓ or ✗? ∴ D becomes [___], DEQUEUE() removes first 2, D.front()=2==2 ✓ → pop → D=[___], DEQUEUE() removes second 2, D.front()=??? → ___, ∴ <= is wrong/correct because ___.

00. FAILURE PREDICTIONS (fill after completing all steps):
F1. ________________________________
F2. ________________________________
F3. forget D.push_back(x) → ________
F4. pop D on every dequeue → ________
F5. use std::vector → pop_front costs O(___)
F6. forget D.empty() check → ________
F7. use <= instead of < → ________

═══════════════════════════════════════════════════════════════════════════════
ERROR REPORT
═══════════════════════════════════════════════════════════════════════════════

E1. Line 82-90 findmin()
    WHAT: d.front() called without empty check
    WRONG: return d.front(); when d=[]
    RIGHT: if (d.empty()) throw; return d.front();
    WHY SLOPPY: skipped edge case, rushed to return statement
    MISSED: worksheet step 28 says "Q=[], D=[], findmin() → CRASH"
    PREVENT: always write edge case FIRST, then logic

E2. Line 82-86 findmin()
    WHAT: comment says "YOUR CODE" but code not written
    WRONG: left placeholder comment, wrote code below it
    RIGHT: replace placeholder with actual code
    WHY SLOPPY: read comment, ignored it, typed below
    MISSED: comment explicitly says "if (___) throw"
    PREVENT: delete placeholder comments after implementing

QUESTIONS TO SLOPPY BRAIN:
Q1. worksheet step 28 says d.front() on empty d → crash, did you read it?
Q2. test_empty_exception exists, did you trace what happens?
Q3. line 84-86 has template code, did you fill it or skip it?
Q4. 5/6 tests passed, did you assume code is correct?
Q5. error message says "FAILED: Expected exception", did you read it?

ORTHOGONAL THOUGHT:
- enqueue() has while loop guard: d.size() > 0 → you wrote guard there
- dequeue() has if guard: q.front() == d.front() → you wrote guard there
- findmin() needs guard: d.empty() → you skipped guard here
- PATTERN: every function accessing container needs empty check
- YOU: wrote guards for 2/3 functions, forgot 1/3

TEST RESULTS BEFORE FIX:
test_basic       ✓
test_decreasing  ✓
test_increasing  ✓
test_duplicates  ✓
test_mixed       ✓
test_empty_exception ✗ → d.front() on empty d → crash

FIX APPLIED:
Line 82-90: added if (d.empty()) throw before return d.front();

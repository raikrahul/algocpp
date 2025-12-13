# SuperStack: O(1) Push, Pop, FindMax

01. PROBLEM: push(x)=O(1), pop()=O(1), findMax()=O(1) → stack + max tracking → DRAW empty stack as vertical boxes: |_|←top, max=∅, size=0 → WRITE struct SuperStack { stack<int> data; ??? max_tracker; } → QUESTION: max_tracker type=??? → DO NOT ANSWER YET.

02. NAIVE TRAP: findMax() scans entire stack → push(5),push(3),push(8),push(2) → findMax() scans [5,3,8,2] bottom-to-top → 4 comparisons → O(n) ✗ → DRAW: |2|←top, |8|, |3|, |5|←bottom → scan↓↓↓↓ → max=8 found at position 2 from bottom → FAILURE: O(n) per findMax call → n pushes + n findMax = O(n²) total ✗.

03. TRAP: single max variable → push(5)→max=5, push(3)→max=5, push(8)→max=8, push(2)→max=8 → DRAW: |2|←top, |8|, |3|, |5|, max_var=8 → pop()→removes 2→max_var=8 ✓ → pop()→removes 8→max_var=??? → LOST HISTORY → previous max was 5 but we forgot → max_var cannot recover without scan → O(n) scan needed → FAILURE: pop() breaks O(1) findMax.

04. INSIGHT from failure F3: need max HISTORY not single value → when 8 popped, need to know max was 5 before 8 arrived → HISTORY = sequence of max values at each state → DRAW timeline: state₀→max=∅, state₁(push 5)→max=5, state₂(push 3)→max=5, state₃(push 8)→max=8, state₄(push 2)→max=8 → pop at state₄ returns to state₃ → max must revert to state₃'s max=8, BUT pop at state₃ returns to state₂ → max must revert to state₂'s max=5 → HISTORY stored WHERE??? → STACK tracks history naturally → second stack for max history.

05. SECOND STACK IDEA: main_stack=[5,3,8,2]←top, max_stack=[5,5,8,8]←top → DRAW side-by-side: main|max → |2|8|, |8|8|, |3|5|, |5|5| → findMax()=max_stack.top()=8 → O(1) ✓ → pop() main_stack.pop()=2, max_stack.pop()=8 → new state: main=[5,3,8], max=[5,5,8] → findMax()=max_stack.top()=8 → O(1) ✓ → pop() again: main=[5,3], max=[5,5] → findMax()=5 ✓ → WORKS but COST: n pushes = 2n total pushes (main+max) → space=O(2n)=O(n) → acceptable??? YES for O(1) time.

06. PUSH LOGIC DERIVATION: push(x) → main_stack.push(x) → max_stack.push(???) → IF max_stack empty: push(x) → IF max_stack not empty: push(max(x, max_stack.top())) → TRACE push(5): main=[], max=[] → main.push(5)=[5], max empty → max.push(5)=[5] → TRACE push(3): main=[5], max=[5] → main.push(3)=[5,3], max(3,5)=5 → max.push(5)=[5,5] → TRACE push(8): main=[5,3], max=[5,5] → main.push(8)=[5,3,8], max(8,5)=8 → max.push(8)=[5,5,8] → TRACE push(2): main=[5,3,8], max=[5,5,8] → main.push(2)=[5,3,8,2], max(2,8)=8 → max.push(8)=[5,5,8,8] → VERIFY by hand: max_stack tracks running max at each depth.

07. POP LOGIC DERIVATION: pop() → main_stack.pop() AND max_stack.pop() → both stacks shrink together → TRACE from state main=[5,3,8,2], max=[5,5,8,8] → pop(): main.pop()→main=[5,3,8], max.pop()→max=[5,5,8] → pop(): main.pop()→main=[5,3], max.pop()→max=[5,5] → pop(): main.pop()→main=[5], max.pop()→max=[5] → pop(): main.pop()→main=[], max.pop()→max=[] → VERIFY: stacks stay synchronized, findMax()=max.top() always valid.

08. EDGE CASE N=0: empty stack → findMax() called → max_stack.top() undefined behavior → MUST CHECK: if(max_stack.empty()) return ??? or throw → DECISION: return INT_MIN or throw exception → DRAW: main=[], max=[] → findMax()→✗ undefined → ADD GUARD: if(empty()) throw/return sentinel.

09. EDGE CASE N=1: push(42) → main=[42], max=[42] → findMax()=42 ✓ → pop() → main=[], max=[] → findMax()→empty guard triggers → TRACE COMPLETE.

10. EDGE CASE ALL SAME: push(7),push(7),push(7) → main=[7,7,7], max=[7,7,7] → findMax()=7 ✓ → pop()→main=[7,7], max=[7,7] → findMax()=7 ✓ → NO SPECIAL HANDLING NEEDED.

11. EDGE CASE DESCENDING: push(9),push(6),push(3),push(1) → main=[9,6,3,1], max=[9,9,9,9] → findMax()=9 ✓ → max_stack stores 9 four times → REDUNDANT but correct → SPACE OPTIMIZATION possible??? → YES: store (value, count) pairs → SKIP for now, basic version first.

12. EDGE CASE ASCENDING: push(1),push(3),push(6),push(9) → main=[1,3,6,9], max=[1,3,6,9] → findMax()=9 ✓ → pop()→main=[1,3,6], max=[1,3,6] → findMax()=6 ✓ → EACH PUSH updates max → max_stack mirrors main_stack in this case → WORST CASE for space.

13. NUMERICAL SIMULATION LARGE: push sequence [10,4,15,2,15,8,3] → STEP-BY-STEP with memory addresses: addr 0x100=main_stack, addr 0x200=max_stack → push(10): main@0x100=[10], max@0x200=[10] → push(4): main=[10,4], max(4,10)=10, max=[10,10] → push(15): main=[10,4,15], max(15,10)=15, max=[10,10,15] → push(2): main=[10,4,15,2], max(2,15)=15, max=[10,10,15,15] → push(15): main=[10,4,15,2,15], max(15,15)=15, max=[10,10,15,15,15] → push(8): main=[10,4,15,2,15,8], max(8,15)=15, max=[10,10,15,15,15,15] → push(3): main=[10,4,15,2,15,8,3], max(3,15)=15, max=[10,10,15,15,15,15,15] → findMax()=15 ✓ → DRAW FINAL STATE:
```
main_stack@0x100:        max_stack@0x200:
|3 |←top idx=6           |15|←top idx=6
|8 |    idx=5            |15|    idx=5
|15|    idx=4            |15|    idx=4
|2 |    idx=3            |15|    idx=3
|15|    idx=2            |15|    idx=2
|4 |    idx=1            |10|    idx=1
|10|←bottom idx=0        |10|←bottom idx=0
```

14. POP SEQUENCE from state above: pop()→main=[10,4,15,2,15,8], max=[10,10,15,15,15,15], findMax()=15 ✓ → pop()→main=[10,4,15,2,15], max=[10,10,15,15,15], findMax()=15 ✓ → pop()→main=[10,4,15,2], max=[10,10,15,15], findMax()=15 ✓ → pop()→main=[10,4,15], max=[10,10,15], findMax()=15 ✓ → pop()→main=[10,4], max=[10,10], findMax()=10 ✓ (MAX CHANGED from 15 to 10) → pop()→main=[10], max=[10], findMax()=10 ✓ → pop()→main=[], max=[], findMax()=EMPTY GUARD.

15. VERIFY COMPLEXITY: push(x)→main.push O(1) + max comparison O(1) + max.push O(1) = O(1) ✓ → pop()→main.pop O(1) + max.pop O(1) = O(1) ✓ → findMax()→max.top() O(1) = O(1) ✓ → SPACE: 2 stacks each up to n elements = O(2n) = O(n) → ALL REQUIREMENTS MET.

16. ALTERNATIVE: store delta instead of actual max → push(x): if stack empty, push x, max=x; else push(x-max), if x>max then max=x → pop(): if top>0, old_max=max; else max=max-top; pop → COMPLEX, error-prone → SKIP for clarity → BASIC TWO-STACK solution preferred for correctness over cleverness.

17. CODE STRUCTURE TO WRITE: class SuperStack { private: stack<int> main_stack; stack<int> max_stack; public: void push(int x); void pop(); int findMax(); bool empty(); int top(); } → WRITE BOILERPLATE ONLY, NO IMPLEMENTATION.

---

## FAILURE PREDICTIONS

F1. FORGETTING max_stack.push on every main_stack.push → max_stack gets out of sync → findMax() returns stale value → SYMPTOM: after push, findMax returns old max → FIX: always push to BOTH stacks.

F2. FORGETTING max_stack.pop on every main_stack.pop → stacks diverge → max_stack grows unbounded → SYMPTOM: after pop, findMax returns wrong value → FIX: always pop from BOTH stacks.

F3. USING max instead of max_stack.top() in push → old_max = class member, gets overwritten → SYMPTOM: running max lost after multiple pushes → FIX: max_stack.top() is the previous max, not a member variable.

F4. EMPTY CHECK missing before top() call → undefined behavior on empty stack → SYMPTOM: crash or garbage value → FIX: guard with if(!empty()) before any top() call.

F5. RETURNING max_stack.top() when max_stack empty → UB crash → SYMPTOM: segfault on empty stack → FIX: check empty(), return sentinel or throw.

F6. COMPARING x >= max_stack.top() instead of max(x, max_stack.top()) → thinking greater-or-equal matters → SYMPTOM: none, both work, but conceptually max() clearer.

F7. POPPING only main_stack, forgetting max_stack → classic desync bug → SYMPTOM: findMax() incorrect after pop → FIX: pop BOTH always.

F8. THINKING findMax removes the max element → confusion with extractMax from heap → SYMPTOM: stack corrupted after findMax → FIX: findMax is query-only, READ not REMOVE.

F9. IMPLEMENTING with single stack + scanning on pop → defeats purpose → O(n) pop → SYMPTOM: TLE on many pops → FIX: two stacks, O(1) pop.

F10. USING std::max_element on main_stack → O(n) per findMax → naive implementation → SYMPTOM: TLE → FIX: second stack approach.

---

## MISTAKES MADE DURING IMPLEMENTATION

M1. LINE 39: `max_stack.pop()` → MISSING SEMICOLON → compiler error → `max_stack.pop();` → WHY SLOPPY: rushed typing, no compile check after each function → PREVENT: compile after each function body.

M2. LINE 64: `return max_stack.size();` → WRONG STACK for size() → functionally same (stacks synchronized) but semantically wrong → `return main_stack.size();` → WHY SLOPPY: copy-paste from findMax without thinking → PREVENT: read what function returns, main_stack holds user data, max_stack is auxiliary.

M3. LINE 36-40: left `// YOUR CODE HERE` comment → dead comment after implementation → remove or keep for clarity → WHY SLOPPY: did not clean up placeholder → PREVENT: remove placeholder after implementing.

M4. LINE 23: `if ( max_stack.empty())` → extra space after `(` → inconsistent style → `if (max_stack.empty())` → WHY SLOPPY: muscle memory from other languages → PREVENT: consistent formatting.

M5. GENERAL: no empty() guard in findMax(), top() → if called on empty stack → undefined behavior → WHY SLOPPY: assumed tests always call with valid state → PREVENT: add guard or document precondition.


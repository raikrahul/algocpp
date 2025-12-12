1. 01. RAW DATA INPUT: P1_ID=10, P1_CONTENT="apple banana". P2_ID=20, P2_CONTENT="banana cherry". P3_ID=30, P3_CONTENT="apple cherry".
2. 02. MEMORY STATE INITIAL: `index` is empty Map<String, Vector<int>>. `index` = {}.
3. 03. PROCESS P1 (10, "apple banana"):
4. 04. Token "apple": `index` has no key "apple". Create key. Value = empty vector. Add 10. `index` = {"apple": [10]}.
5. 05. Token "banana": `index` has no key "banana". Create key. Value = empty vector. Add 10. `index` = {"apple": [10], "banana": [10]}.
6. 06. PROCESS P2 (20, "banana cherry"):
7. 07. Token "banana": `index` has key "banana". Current list = [10]. New ID 20. 20 > 10. Append 20. `index["banana"]` = [10, 20].
8. 08. Token "cherry": `index` has no key "cherry". Create key. Add 20. `index` = {"apple": [10], "banana": [10, 20], "cherry": [20]}.
9. 09. PROCESS P3 (30, "apple cherry"):
10. 10. Token "apple": `index` has key "apple". Current list = [10]. New ID 30. 30 > 10. Append 30. `index["apple"]` = [10, 30].
11. 11. Token "cherry": `index` has key "cherry". Current list = [20]. New ID 30. 30 > 20. Append 30. `index["cherry"]` = [20, 30].
12. 12. FINAL STATE:
13.     "apple" -> [10, 30]
14.     "banana" -> [10, 20]
15.     "cherry" -> [20, 30]
16. 
17. 13. QUERY OPERATION: Find pages with BOTH "apple" AND "banana".
18. 14. FETCH LISTS: L1 = index["apple"] = [10, 30]. L2 = index["banana"] = [10, 20].
19. 15. INTERSECTION TRACE (L1=[10, 30], L2=[10, 20]):
20. 16. i=0, j=0. L1[0]=10. L2[0]=10.
21. 17. 10 == 10. MATCH. Add 10 to Result. Result = [10]. Increment i->1, j->1.
22. 18. i=1, j=1. L1[1]=30. L2[1]=20.
23. 19. 30 > 20. L2 is smaller. We need larger value in L2 to match 30. Increment j->2.
24. 20. i=1, j=2. L2 size is 2. j=2 means END of L2.
25. 21. Loop Terminate.
26. 22. QUERY RESULT: [10].
27. 
28. 23. QUERY OPERATION 2: Find pages with BOTH "apple" AND "cherry".
29. 24. FETCH LISTS: L1 = index["apple"] = [10, 30]. L2 = index["cherry"] = [20, 30].
30. 25. INTERSECTION TRACE (L1=[10, 30], L2=[20, 30]):
31. 26. i=0, j=0. L1[0]=10. L2[0]=20.
32. 27. 10 < 20. L1 is smaller. Increment i->1.
33. 28. i=1, j=0. L1[1]=30. L2[0]=20.
34. 29. 30 > 20. L2 is smaller. Increment j->1.
35. 30. i=1, j=1. L1[1]=30. L2[1]=30.
36. 31. 30 == 30. MATCH. Add 30 to Result. Result = [30]. Increment i->2, j->2.
37. 32. Both at END.
38. 33. QUERY RESULT: [30].
39. 
40. 34. FAILURE PREDICTION (Duplicate words in one page):
41. 35. INPUT: P4_ID=40, P4_CONTENT="dog dog".
42. 36. Token 1 "dog": `index["dog"]` (assume empty) -> [40].
43. 37. Token 2 "dog": `index["dog"]` is [40]. Last element is 40. New ID is 40.
44. 38. 40 == 40. DO NOT ADD. List remains [40].
45. 39. JUSTIFICATION: Index must store unique page IDs. Sorted Vector requirement.
46. 
47. 40. FAILURE PREDICTION (Empty Query):
48. 41. INPUT: Query Words = [].
49. 42. Logic: "contain all words". Start with Universal Set? No, usually start with nothing.
50. 43. Defined behavior: Empty query returns empty result.
51. 
52. 44. CODE STRUCTURE:
53. 45. `addPage(id, content)`: Loop tokens. Check `if (list.empty() || list.back() != id) list.push_back(id)`.
54. 46. `query(words)`: Sort words by list size? (Optimization). For now, strict sequential intersection.
55. 46. `intersect(v1, v2)`: The while loop derived in steps 16-21 and 26-32.

---

ERROR REPORT (2025-12-12):

E1. POTENTIAL: LINE 56 → `list.back()` on empty vector → undefined behavior
→ SLOPPY: assumed list non-empty
→ MISSED: `list.empty()` check must come BEFORE `list.back()`
→ PREVENT: always check `.empty()` before `.back()` or `.front()`
→ CODE HAS: `if (list.empty() || list.back() != page.id)` → short-circuit evaluation → ✓

E2. POTENTIAL: LINE 69 → forgot `process_word(current_word)` after loop
→ SLOPPY: assumed all words end with space
→ MISSED: "apple banana" has NO trailing space → "banana" never processed
→ TRACE: "apple banana"[11] = 'a' → no more chars → loop ends → current_word="banana" → lost
→ PREVENT: always process remaining buffer after character loop
→ CODE HAS: `process_word(current_word);` after for-loop → ✓

E3. POTENTIAL: LINE 78-81 → query words not normalized
→ SLOPPY: assumed user input matches index format
→ MISSED: addPage lowercases, query must lowercase too
→ TRACE: addPage("Apple") → index["apple"]=[10], query({"Apple"}) → index.find("Apple") → end → []
→ PREVENT: normalize input in both addPage AND query
→ CODE HAS: normalization loop in query → ✓

E4. POTENTIAL: LINE 94 → word not in index returns {}
→ SLOPPY: could return partial intersection instead of empty
→ MISSED: AND semantics → missing word means result is empty set
→ TRACE: query({"apple", "xyz"}) → index.find("xyz") == end → ∅ ∩ {10,30} = ∅
→ PREVENT: clarify AND vs OR semantics upfront
→ CODE HAS: `if (it2 == index.end()) return {};` → ✓

E5. POTENTIAL: LINE 92-97 → intersection order matters for performance
→ SLOPPY: intersect in input order
→ MISSED: intersect smallest list first reduces work
→ TRACE: L1=[1..1000000], L2=[1] → intersect(L1, L2) scans L1 fully
→ TRACE: L1=[1], L2=[1..1000000] → intersect(L1, L2) stops at i=1
→ PREVENT: sort words by list size before intersecting
→ CODE: optimization not implemented → acceptable for problem scope

ORTHOGONAL THOUGHTS:

O1. Brain wrote `list.back()` → assumed non-empty
→ Orthogonal: what if list IS empty? → crash
→ Did not ask: "what is the state of list BEFORE I call .back()?"

O2. Brain wrote for-loop → assumed boundary at space
→ Orthogonal: what if string has no trailing space?
→ Did not ask: "what happens to chars buffered when loop ends?"

O3. Brain wrote query → assumed input format matches
→ Orthogonal: what if input has different case?
→ Did not ask: "who controls input format?"

QUESTIONS TO ASK BEFORE EACH LINE:
Q1. What is the current state of all variables?
Q2. What assumptions am I making?
Q3. What if assumption is wrong?
Q4. What happens at boundary conditions?

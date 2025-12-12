1. 01. Define Page: ID (integer), Content (string of words). Example: P1="A B", P2="B C". Input = [P1, P2]. Index = Map<Word, List<PageID>>. Ideally List is Sorted unique integers.
2. 02. Process P1 (ID=1, Content="A B") → Words=["A", "B"].
3. 03. Word "A": `index["A"]` is empty. Add 1. `index["A"] = {1}`.
4. 04. Word "B": `index["B"]` is empty. Add 1. `index["B"] = {1}`.
5. 05. Process P2 (ID=2, Content="B C") → Words=["B", "C"].
6. 06. Word "B": `index["B"]` is `{1}`. Add 2. `index["B"] = {1, 2}`. Preserves sort order since 2 > 1.
7. 07. Word "C": `index["C"]` is empty. Add 2. `index["C"] = {2}`.
8. 08. Final Index: A→{1}, B→{1,2}, C→{2}.
9. 09. Duplicate Word Edge Case: P3="D D". ID=3. Words=["D", "D"].
10. 10. 1st "D": `index["D"]` empty → {3}.
11. 11. 2nd "D": `index["D"]` is {3}. Last element is 3. 3 == 3. Do not add. List remains {3}. Unique requirement satisfied.
12. 12. Implementation: `std::map<string, std::vector<int>>`. Vector chosen over Set for O(1) append at end (assuming sequential page processing).
13. 13. Query requirement: "contain at least one occurrence of **each** of the query words" → AND operation → Intersection of lists.
14. 14. Query Q1 = "B". Look up "B" → {1, 2}. Result: {1, 2}.
15. 15. Query Q2 = "A B". Look up "A" → L1={1}. Look up "B" → L2={1, 2}.
16. 16. Intersect L1, L2.
17. 17. Ptr1 points to L1[0]=1. Ptr2 points to L2[0]=1.
18. 18. 1 == 1. Match! Add 1 to Result. Advance Ptr1, Ptr2.
19. 19. Ptr1 at End. Stop. Result = {1}. Correct (P1 has A and B).
20. 20. Query Q3 = "A C". L1={1}, L2={2}.
21. 21. Ptr1 at 1. Ptr2 at 2. 1 < 2. Advance Ptr1.
22. 22. Ptr1 at End. Stop. Result = {}. Correct (No page has A and C).
23. 23. Query Q4 = "X". Look up "X" → Empty. Result = {}.
24. 24. Multi-word intersect logic: With k words, intersect word1 and word2 → res. Then intersect res and word3 → res...
25. 25. Optimization: Start with list of smallest size? Sort query words by freq? For this problem N is small, sequential intersect is O(K * TotalWords). Fine.
26. 26. Case Sensitivity: "Apple" vs "apple". Requirement not specified. Assumption: Convert all to lowercase.
27. 27. Punctuation: "end." vs "end". Remove punctuation. `std::isalnum`.
28. 28. F1: Forgot to sort result? IDs added in increasing order of PageID. Vectors are naturally sorted. Intersection preserves order.
29. 29. F2: Intersection bug. `1` vs `1`. If code increments only one pointer on match, might duplicate or skip? Standard algo: if equal, add, increment BOTH.
30. 30. F3: Empty query. Return empty list? Or all pages? "contain each of query words". Vacuum is true? No, usually empty query returns nothing.
31. 31. Data Structure: `struct Page { int id; string content; };`
32. 32. Helper: `vector<string> tokenize(string)` -> lowercases, splits by space, removes non-alnum.
33. 33. Class `InvertedIndex`. `void addPage(const Page& p)`. `vector<int> query(const vector<string>& words)`.
34. 34. Memory: String storage dominates. `std::map` adds overhead. `std::vector` overhead minimal.
35. 35. Time: Build O(TotalWords * log(DistinctWords)). Query O(QueryLen * MaxListSize).
36. 
37. ---
38. 
39. SELF-CHECK:
40. - Logic derived from simple examples (P1, P2).
41. - Intersection logic traced with pointers.
42. - Duplicate handling in same page handled (Line 11).
43. - Data structures chosen (Line 12).
44. 
45. ERROR REPORT PREDICTION:
46. E1. `tokenize` leaves empty strings if multiple spaces? "A  B".
47. -> Trace: "A", "", "B".
48. -> Code must skip empty tokens.
49. 
50. E2. `query` with word not in index.
51. -> `index.find("X")` returns `end`.
52. -> `index["X"]` would create empty entry if using `operator[]`.
53. -> `operator[]` is not const. Query should be const.
54. -> Use `find`. If not found, treat as empty list.
55. -> Intersection with empty list is empty. Efficient early exit.

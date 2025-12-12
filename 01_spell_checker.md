input→output
file_words=[hello,wrld,test,speling], dict_words=[hello,world,test,spelling] → incorrect=[wrld,speling]
file_words=[cat,dog,brd], dict_words=[cat,dog,bird] → incorrect=[brd]
file_words=[apple,banana], dict_words=[apple,banana] → incorrect=[]

01. file_words=5, dict_words=1000 → check_count=5, lookup_operations=5
02. file_words=5, dict_words=1000, linear_search → time=5×1000=5000 comparisons
03. file_words=5, dict_words=1000, sorted_dict, binary_search → time=5×log₂(1000)=5×10=50 comparisons
04. 5000 vs 50 → ratio=100× slower (linear vs binary)
05. file_words=10000, dict_words=100000, linear → time=10000×100000=1000000000 comparisons
06. file_words=10000, dict_words=100000, sorted+binary → time=10000×log₂(100000)=10000×17=170000 comparisons
07. 1000000000 vs 170000 → ratio=5882× slower (linear vs binary)
08. dict_words=100000, hash_table, load_time=100000 operations, lookup_time=O(1)
09. file_words=10000, hash_lookup → time=10000×1=10000 comparisons
10. 170000 vs 10000 → ratio=17× slower (binary vs hash)
11. dict_words=[cat,dog,bird], build_hash → hash(cat)=h₁, hash(dog)=h₂, hash(bird)=h₃
12. hash_table[h₁]=cat, hash_table[h₂]=dog, hash_table[h₃]=bird → size=3
13. file_word=brd → hash(brd)=h₄ → hash_table[h₄]=∅ → ∴ incorrect ✓
14. file_word=cat → hash(cat)=h₁ → hash_table[h₁]=cat → ∴ correct ✓
15. collision: hash(cat)=hash(act)=h₁ → hash_table[h₁]=[cat,act] → chain_length=2
16. lookup cat → hash(cat)=h₁ → chain=[cat,act] → compare cat==cat ✓ → found
17. lookup dog → hash(dog)=h₂ → chain=[dog] → compare dog==dog ✓ → found
18. lookup xyz → hash(xyz)=h₅ → chain=∅ → ∴ not_found ✗
19. dict_size=100000, hash_table_size=100000, load_factor=1.0 → avg_chain_length=1
20. dict_size=100000, hash_table_size=50000, load_factor=2.0 → avg_chain_length=2
21. load_factor=1.0 → lookup_time=O(1), load_factor=2.0 → lookup_time=O(2)=O(1)
22. load_factor=10.0 → lookup_time=O(10)=O(1) but slower
23. file_words=[hello,wrld,test], dict_words=[hello,world,test,spelling]
24. build_hash: hash(hello)=0x100, hash(world)=0x108, hash(test)=0x110, hash(spelling)=0x118
25. hash_table: 0x100→hello, 0x108→world, 0x110→test, 0x118→spelling
26. check hello → hash(hello)=0x100 → hash_table[0x100]=hello → match ✓ → correct
27. check wrld → hash(wrld)=0x120 → hash_table[0x120]=∅ → no_match ✗ → incorrect
28. check test → hash(test)=0x110 → hash_table[0x110]=test → match ✓ → correct
29. incorrect_list=[wrld] → count=1
30. dict_words=[cat,dog,bird], sort → [bird,cat,dog]
31. sorted_dict: index₀=bird, index₁=cat, index₂=dog
32. file_word=cat → binary_search: low=0, high=2, mid=(0+2)/2=1
33. sorted_dict[1]=cat → cat==cat ✓ → found
34. file_word=brd → binary_search: low=0, high=2, mid=1
35. sorted_dict[1]=cat → brd<cat → high=mid-1=0
36. low=0, high=0, mid=0 → sorted_dict[0]=bird → brd<bird → high=-1
37. low>high → not_found ✗ → incorrect
38. file_word=xyz → binary_search: low=0, high=2, mid=1
39. sorted_dict[1]=cat → xyz>cat → low=mid+1=2
40. low=2, high=2, mid=2 → sorted_dict[2]=dog → xyz>dog → low=3
41. low>high → not_found ✗ → incorrect
42. dict_size=8 → sort_time=8×log₂(8)=8×3=24 comparisons
43. dict_size=1024 → sort_time=1024×log₂(1024)=1024×10=10240 comparisons
44. dict_size=100000 → sort_time=100000×log₂(100000)=100000×17=1700000 comparisons
45. file_words=5, dict_words=1000, unsorted → time=5×1000=5000
46. file_words=5, dict_words=1000, sorted → time=sort_time+search_time=1000×10+5×10=10000+50=10050
47. 5000 vs 10050 → sorting_overhead=2× slower (one-time check)
48. file_words=10000, dict_words=1000, unsorted → time=10000×1000=10000000
49. file_words=10000, dict_words=1000, sorted → time=1000×10+10000×10=10000+100000=110000
50. 10000000 vs 110000 → ratio=90× faster (sorted wins)
51. dict_words=[cat,dog,bird], trie_root=∅
52. insert cat: root→c→a→t→end_marker
53. insert dog: root→d→o→g→end_marker
54. insert bird: root→b→i→r→d→end_marker
55. trie_structure: root→{b→{i→{r→{d→end}}}, c→{a→{t→end}}, d→{o→{g→end}}}
56. search cat: root→c(✓)→a(✓)→t(✓)→end(✓) → found
57. search brd: root→b(✓)→r(✗) → not_found
58. search dog: root→d(✓)→o(✓)→g(✓)→end(✓) → found
59. dict_size=100000, avg_word_length=5 → trie_nodes≈100000×5=500000
60. hash_table_size=100000 → space=100000 slots
61. trie_space=500000 nodes vs hash_space=100000 slots → ratio=5× more
62. trie_lookup_time=O(word_length), hash_lookup_time=O(1)
63. word_length=5 → trie_time=5 operations, hash_time=1 operation
64. word_length=20 → trie_time=20 operations, hash_time=1 operation
65. file_words=[hello,wrld,test,speling,xyz], dict_words=[hello,world,test,spelling]
66. method=hash_table → build_time+lookup_time
67. build_time: insert 4 words → 4 operations
68. lookup_time: check 5 words → 5 operations
69. total_time=4+5=9 operations
70. method=sorted_array → sort_time+lookup_time
71. sort_time: 4×log₂(4)=4×2=8 operations
72. lookup_time: 5×log₂(4)=5×2=10 operations
73. total_time=8+10=18 operations
74. 9 vs 18 → hash=2× faster
75. case_sensitive: Hello≠hello → hash(Hello)≠hash(hello)
76. case_insensitive: Hello==hello → normalize→lowercase→hash(hello)=hash(hello)
77. file_word=Hello, dict_word=hello, case_sensitive → not_found ✗
78. file_word=Hello, dict_word=hello, case_insensitive → normalize→hello → found ✓
79. punctuation: hello,→strip→hello
80. file_word=hello,, dict_word=hello → strip_punctuation→hello → found ✓
81. file_word=hello,, dict_word=hello, no_strip → hash(hello,)≠hash(hello) → not_found ✗
82. whitespace: " hello "→strip→"hello"
83. file_word=" hello ", dict_word="hello" → strip_whitespace→"hello" → found ✓
84. numbers: hello123→contains_digits→skip or check
85. file_word=hello123, dict_word=hello → no_match ✗
86. file_word=hello123, filter_alphanumeric→hello → match ✓
87. empty_file: file_words=[] → incorrect=[] → time=0
88. empty_dict: dict_words=[] → all_incorrect → file_words=[cat,dog] → incorrect=[cat,dog]
89. single_word_file: file_words=[cat], dict_words=[cat,dog] → incorrect=[]
90. single_word_dict: dict_words=[cat], file_words=[cat,dog] → incorrect=[dog]
91. all_correct: file_words=[cat,dog], dict_words=[cat,dog,bird] → incorrect=[]
92. all_incorrect: file_words=[xyz,abc], dict_words=[cat,dog] → incorrect=[xyz,abc]
93. duplicates_in_file: file_words=[cat,cat,dog], dict_words=[cat,dog] → check_cat_twice or deduplicate
94. deduplicate: file_words=[cat,cat,dog]→unique=[cat,dog] → check_count=2
95. no_deduplicate: file_words=[cat,cat,dog] → check_count=3
96. duplicates_in_dict: dict_words=[cat,cat,dog] → hash_table ignores duplicates → size=2
97. memory: dict_size=100000, avg_word_length=10, hash_table → space=100000×10=1000000 bytes
98. memory: dict_size=100000, sorted_array → space=100000×10=1000000 bytes
99. memory: dict_size=100000, trie → space=100000×10×5=5000000 bytes (5× more)
100. file_size=1GB, dict_size=100MB → load_dict_first → memory=100MB
101. file_size=1GB, dict_size=100MB, stream_file → memory=100MB+buffer
102. load_entire_file: file_size=1GB → memory=1GB+100MB=1.1GB
103. stream_file: file_size=1GB, buffer=1MB → memory=100MB+1MB=101MB
104. 1.1GB vs 101MB → ratio=10× less memory (streaming)

F1. forgot_to_build_dict → lookup_fails → all_words_incorrect ✗
F2. case_mismatch → Hello vs hello → not_found ✗ → expected=found
F3. punctuation_not_stripped → hello, vs hello → not_found ✗ → expected=found
F4. hash_collision_not_handled → multiple_words_same_hash → lost_words ✗
F5. binary_search_on_unsorted → incorrect_results ✗
F6. off_by_one_in_binary_search → mid=(low+high)/2 vs mid=low+(high-low)/2 → overflow ✗
F7. empty_dict_not_checked → all_words_marked_incorrect ✗
F8. empty_file_not_checked → unnecessary_dict_load ✗
F9. duplicates_counted_multiple_times → incorrect_count ✗
F10. memory_overflow → file_too_large → crash ✗
F11. trie_end_marker_missing → prefix_matches_incorrectly → cat matches catch ✗
F12. hash_function_poor → all_collisions → O(n) lookup ✗

space_complexity: hash_table=O(dict_size), sorted_array=O(dict_size), trie=O(dict_size×avg_word_length)
time_complexity: hash_build=O(dict_size), hash_lookup=O(file_size), total=O(dict_size+file_size)
time_complexity: sort_build=O(dict_size×log(dict_size)), binary_lookup=O(file_size×log(dict_size)), total=O(dict_size×log(dict_size)+file_size×log(dict_size))
time_complexity: trie_build=O(dict_size×avg_word_length), trie_lookup=O(file_size×avg_word_length), total=O((dict_size+file_size)×avg_word_length)

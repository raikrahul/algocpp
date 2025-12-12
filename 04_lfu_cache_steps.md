01. C=3, ops=[put(1,10),put(2,20),put(3,30),get(1),get(1),put(4,40)] → expected: get(2)=-1, get(1)=10, get(3)=30, get(4)=40 → goal: evict key with min access count → AXIOMATIC: problem statement defines input/output, no new inference

02. naive: int arr[3] → arr[0]=(1,10), arr[1]=(2,20), arr[2]=(3,30) → get(1): for(i=0;i<3;i++) if(arr[i].key==1) return arr[i].val → 3 comparisons max → O(n) ✗ → AXIOMATIC: O(n) derived from loop 0..n-1

03. O(n) lookup fails → need O(1) → hash table → `unordered_map<int,?> m` → m[key]=? → hash(key)%buckets → bucket[hash] → O(1) avg → AXIOMATIC: hash table gives O(1) by definition

04. m[key] stores what? → put(1,10) stores val=10 → get(1) returns 10 → ∴ m[1].val=10 → also need freq for eviction → m[1].freq=1 → `struct Entry{int val; int freq;};` → `unordered_map<int,Entry> m;` → AXIOMATIC: val from problem, freq from "least frequently used"

05. get(1): m.count(1)=1 ✓ → m[1]={10,1} → m[1].freq++=2 → return m[1].val=10 → O(1) ✓ → AXIOMATIC: freq++ because access increases frequency, return val because get() returns value

06. put(4,40): size=3=cap → evict → which key? → min freq → m[1].freq=3, m[2].freq=1, m[3].freq=1 → min=1 → scan all keys O(n) ✗ → AXIOMATIC: min requires comparison of all elements without ordering

07. O(n) scan fails → group by freq → bucket[1]={keys with freq=1} → bucket[freq]=list<int> → `unordered_map<int,list<int>> freqMap` → freqMap[1]=[2,3], freqMap[3]=[1] → AXIOMATIC: grouping by freq avoids scan, list maintains order

08. evict: need min freq among all buckets → track minFreq=1 → freqMap[minFreq].front()=2 → evict 2 → O(1) ✓ → AXIOMATIC: minFreq variable avoids scanning all buckets

09. tie among freq=1 keys {2,3} → which to evict? → "least recently used among same freq" → list front=LRU, back=MRU → freqMap[1]=[2,3] means 2 inserted before 3 → evict front=2 → AXIOMATIC: list order = insertion order = LRU order

10. get(3): m[3].freq=1→2 → key=3 must move from freqMap[1] to freqMap[2] → remove 3 from freqMap[1] → freqMap[1].remove(3) → scan list to find 3 → O(n) ✗ → AXIOMATIC: list has no index, must scan

11. O(n) removal fails → store iterator → iterator=address of node in list → `list<int>::iterator it` → it=0x100 points to node(3) in list → list.erase(it) → O(1) ✓ → AXIOMATIC: erase(iterator) is O(1) by list implementation

12. store iterator where? → m[key].it → `struct Entry{int val; int freq; list<int>::iterator it;};` → m[3]={30,1,0x100} → freqMap[1].erase(m[3].it) → O(1) → AXIOMATIC: Entry already has val,freq, add it field

13. after erase(it), it=0x100 is invalid → after push_back to freqMap[2], new node at 0x200 → must update m[3].it=0x200 → m[3].it=--freqMap[2].end() → AXIOMATIC: erase invalidates iterator, push_back creates new node

14. evict: freqMap[minFreq].front() gives key → m.erase(key) removes from map → freqMap[minFreq].pop_front() removes from list → both required → AXIOMATIC: data in two places, remove from both

15. put(key,val) on existing key: m.count(key)=1 → update m[key].val=val → touch(key) to increase freq → no new node → size unchanged → AXIOMATIC: existing key means update, not insert

16. minFreq update: put() creates node with freq=1 → minFreq=1 → get() increases freq → if freqMap[oldFreq].empty() && oldFreq==minFreq → minFreq++ → AXIOMATIC: new node always freq=1, empty list means no keys at that freq

17. `struct Entry{int val;int freq;list<int>::iterator it;};` `unordered_map<int,Entry> m;` `unordered_map<int,list<int>> freqMap;` `int minFreq;` `int cap;` → AXIOMATIC: each field derived from steps 4,8,12

18. `void touch(int key){int oldF=m[key].freq; freqMap[oldF].erase(m[key].it); if(freqMap[oldF].empty()&&oldF==minFreq)minFreq++; m[key].freq++; int newF=m[key].freq; freqMap[newF].push_back(key); m[key].it=--freqMap[newF].end();}` → AXIOMATIC: erase old, check minFreq, increment, insert new, update iterator

19. `void evict(){int key=freqMap[minFreq].front(); freqMap[minFreq].pop_front(); m.erase(key);}` → AXIOMATIC: front=LRU, pop_front removes, m.erase cleans map

20. `int get(int key){if(!m.count(key))return -1; touch(key); return m[key].val;}` → AXIOMATIC: check exists, touch for freq, return val

21. `void put(int key,int val){if(m.count(key)){m[key].val=val;touch(key);return;} if(m.size()==cap)evict(); Entry e; e.val=val;e.freq=1; freqMap[1].push_back(key); e.it=--freqMap[1].end(); m[key]=e; minFreq=1;}` → AXIOMATIC: check exists, check cap, create entry, insert, update minFreq

22. trace C=3: put(1,10)→m[1]={10,1,it0},freqMap[1]=[1],mf=1 → put(2,20)→m[2]={20,1,it1},freqMap[1]=[1,2],mf=1 → put(3,30)→m[3]={30,1,it2},freqMap[1]=[1,2,3],mf=1 → AXIOMATIC: each put adds to freq=1 list

23. get(1)→touch(1)→erase 1 from freqMap[1]→freqMap[1]=[2,3]→freq++=2→freqMap[2]=[1]→m[1].it=it3→return 10 → AXIOMATIC: move 1 from bucket[1] to bucket[2]

24. get(1)→touch(1)→erase 1 from freqMap[2]→freqMap[2]=∅→2==mf? 2≠1→mf=1→freq++=3→freqMap[3]=[1]→return 10 → AXIOMATIC: bucket[2] empty but mf=1 so no update

25. put(4,40)→m.size()=3=cap→evict()→freqMap[1].front()=2→pop_front→freqMap[1]=[3]→m.erase(2)→insert 4→m[4]={40,1,it4}→freqMap[1]=[3,4]→mf=1 → AXIOMATIC: evict 2, insert 4

26. verify: get(2)→m.count(2)=0→-1 ✓ → get(1)→m[1].val=10 ✓ → get(3)→m[3].val=30 ✓ → get(4)→m[4].val=40 ✓ → AXIOMATIC: matches expected from step 01

27. complexity: get()→m.count O(1)+touch O(1)=O(1) → put()→m.count O(1)+evict O(1)+insert O(1)=O(1) → space→O(cap) entries+O(cap) list nodes=O(cap) → AXIOMATIC: each operation O(1), sum is O(1)

28. edge C=1: put(1,1)→m[1]={1,1,it0}→freqMap[1]=[1]→size=1=cap → put(2,2)→evict→freqMap[1].front()=1→m.erase(1)→insert 2→m[2]={2,1,it1}→freqMap[1]=[2] → get(1)→-1 ✓ → AXIOMATIC: smallest capacity still works

29. edge empty get: get(99)→m.count(99)=0→return -1 → AXIOMATIC: no key means -1

30. edge tie-breaker: C=2,put(1,1),put(2,2)→freqMap[1]=[1,2] → get(1)→freqMap[2]=[1],freqMap[1]=[2] → get(2)→freqMap[2]=[1,2],freqMap[1]=∅→mf=2 → put(3,3)→evict→freqMap[2].front()=1→evict 1→insert 3→freqMap[1]=[3] → AXIOMATIC: when freq tied, LRU=front evicted

---
ERROR REPORT:

E1. Line 20 (old): `}` missing semicolon after Entry struct → `};`
    Why sloppy: copied struct, forgot C++ requires semicolon after struct
    Prevention: compiler error "expected ';' after struct definition"

E2. Line 29-32 (old): duplicate `key_map` and `freq_map` declarations
    Why sloppy: added new maps, forgot to delete old ones
    Prevention: search file for variable name before adding

E3. Line 23 (old): `void touch(std::list<Node>::iterator it)` → Node undefined
    Why sloppy: changed data structure, forgot to update function signature
    Prevention: compile after every change

E4. Line 38 (old): `current_size(0)` in constructor → current_size not declared
    Why sloppy: deleted variable, forgot to remove from constructor
    Prevention: grep for variable name after deletion

E5. Line 30: `freq_map[e.freq++].push_back(key)` → post-increment before push_back
    Why sloppy: tried to be clever with ++, created ambiguous order
    Prevention: never combine ++ with other operations on same line

E6. Line 80 (old): `size == capacity` → size not declared
    Why sloppy: used variable name from mental model, not from code
    Prevention: use key_map.size() explicitly

E7. Line 103 (old): `node.key, node.value` → node is int, not struct
    Why sloppy: assumed freq_map stores Node, actually stores int
    Prevention: trace type through declarations before use

E8. Line 77: missing `return;` after existing key case in put()
    Why sloppy: else branch exists, but control falls through without return
    Prevention: always return/break after handling case

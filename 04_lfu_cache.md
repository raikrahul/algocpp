01. C=3, ops=[put(1,10),put(2,20),put(3,30),get(1),get(1),put(4,40)] → Hand: draw table | Key | Val | Freq |. After put(1,10): |1|10|1|. After put(2,20): |1|10|1|,|2|20|1|. After put(3,30): |1|10|1|,|2|20|1|,|3|30|1|. Size=3=C ✓ Full.

02. get(1) → Hand: freq[1]++ → freq[1]=2. Table: |1|10|2|,|2|20|1|,|3|30|1|. Code: `node->freq++; freqMap[1].remove(node); freqMap[2].push_back(node);` ∴ node moves from list[1] to list[2].

03. get(1) → Hand: freq[1]++ → freq[1]=3. Table: |1|10|3|,|2|20|1|,|3|30|1|. freqMap={1→[2,3], 3→[1]}. minFreq=1 (list[1]≠∅).

04. put(4,40) → Hand: size=3=C → evict. minFreq=1. freqMap[1]=[N2,N3]. LRU=front=N2. Evict key=2. freqMap[1]→[N3]. Insert N4(4,40,f=1). freqMap[1]→[N3,N4]. minFreq=1. Code: `keyMap.erase(2); freqMap[1].pop_front(); Node n4(4,40); freqMap[1].push_back(n4); keyMap[4]=iter(n4);`

05. Final: keyMap={1,3,4}. freqMap={1→[N3,N4], 3→[N1]}. get(2)→-1 ✓. get(1)→10 ✓. get(3)→30 ✓. get(4)→40 ✓.

06. F1: minFreq update? → Hand: after evict, freqMap[minFreq].pop_front(). If freqMap[minFreq].empty() AND minFreq was used? No scan needed. put() always creates node with freq=1 ∴ minFreq=1 after any put(). Code: `if (freqMap[minFreq].empty()) { /* only matters on get(), not put() */ }`

07. F2: get() updates minFreq? → Hand: get(key) → freq[key]++ → oldFreq=minFreq, newFreq=oldFreq+1. If freqMap[oldFreq].empty() AND oldFreq==minFreq → minFreq++. Code: `if (oldFreq == minFreq && freqMap[oldFreq].empty()) minFreq++;`

08. F3: put() on existing key? → Hand: key exists → update val, freq++. Do NOT evict. Do NOT size++. Code: `if (keyMap.count(key)) { auto it = keyMap[key]; it->val = val; touch(it); return; }`

09. Data: keyMap=unordered_map<int, list<Node>::iterator>. freqMap=unordered_map<int, list<Node>>. Hand: draw keyMap[1]→iterator pointing into freqMap[1].list[pos=0]. Code: `std::list<Node>::iterator it = freqMap[1].begin(); keyMap[1] = it;`

10. touch(it): → Hand: oldFreq=it->freq=1. freqMap[1].erase(it) → list becomes shorter. it->freq++=2. freqMap[2].push_back(*it). newIt=--freqMap[2].end(). keyMap[key]=newIt. Code: `int oldF = it->freq; freqMap[oldF].erase(it); it->freq++; int newF = it->freq; freqMap[newF].push_back(*it); keyMap[it->key] = --freqMap[newF].end(); if (freqMap[oldF].empty() && oldF == minFreq) minFreq++;`

11. evict(): → Hand: minFreq=1. Node n = freqMap[1].front(). key=n.key. freqMap[1].pop_front(). keyMap.erase(key). size--. Code: `Node& lfu = freqMap[minFreq].front(); keyMap.erase(lfu.key); freqMap[minFreq].pop_front(); size--;`

12. C=1 trace: put(1,1) → keyMap{1}, freqMap{1→[N1]}, mf=1, sz=1. put(2,2) → sz=1=C, evict mf=1→N1, keyMap{2}, freqMap{1→[N2]}, mf=1, sz=1. get(1)→-1 ✓. get(2)→2 ✓.

13. Tie-breaker C=2: put(1,1), put(2,2) → f(1)=f(2)=1. get(1), get(2) → f(1)=f(2)=2. freqMap={2→[N1,N2]}. put(3,3) → evict mf=2, LRU=front=N1. Evict 1. keyMap{2,3}. get(1)→-1 ✓.

14. Addr trace: N1=0xA, N2=0xB, N3=0xC. put(1,10): freqMap[1]={0xA}. keyMap[1]=iter→0xA. put(2,20): freqMap[1]={0xA,0xB}. keyMap[2]=iter→0xB. get(1): freqMap[1]={0xB}, freqMap[2]={0xA}. keyMap[1]=iter→0xA(in list[2]).

15. Complexity: get() → keyMap.find O(1) + list.erase O(1) + list.push_back O(1) + minFreq check O(1) = O(1). put() → same + evict O(1) = O(1). Space = O(C) nodes + O(C) iterators.

16. Node struct: `struct Node { int key, val, freq; Node(int k, int v) : key(k), val(v), freq(1) {} };` → Hand: N1(1,10,1) occupies 12 bytes (3×int).

17. Class skeleton: `class LFUCache { int cap, sz, minFreq; unordered_map<int, list<Node>::iterator> keyMap; unordered_map<int, list<Node>> freqMap; void touch(iter); void evict(); public: LFUCache(int c); int get(int k); void put(int k, int v); void clear(); };`

---
Self-Check:
- Line 06: minFreq=1 after put() derived from "new node always has freq=1".
- Line 07: minFreq++ on get() derived from "oldFreq list may become empty".
- Line 09: iterator storage derived from "need O(1) erase from list".
- Line 10: touch() sequence derived from "freq++ means move between lists".
- No jumps. Each step uses previous state.

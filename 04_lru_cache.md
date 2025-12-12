01. C=2, ops=[put(1,1),put(2,2),get(1),put(3,3)] → Hand: draw DLL [Head]⇄[?]⇄[?]⇄[Tail]. After put(1,1): [H]⇄[N1:1,1]⇄[T]. Map={1→N1}. After put(2,2): [H]⇄[N2:2,2]⇄[N1:1,1]⇄[T]. Map={1→N1,2→N2}. Size=2=C ✓ Full.

02. get(1) → Hand: find N1 in map. Detach N1: prev=N2, next=T. N2→next=T, T→prev=N2. Attach N1 at head: H→next=N1, N1→prev=H, N1→next=N2, N2→prev=N1. Result: [H]⇄[N1]⇄[N2]⇄[T]. Code: `remove(node); addToHead(node);` Return 1.

03. put(3,3) → Hand: sz=2=C → evict. LRU=Tail→prev=N2. Detach N2: prev=N1, next=T. N1→next=T, T→prev=N1. map.erase(2). delete N2. Create N3(3,3). Attach N3 at head. [H]⇄[N3]⇄[N1]⇄[T]. Map={1→N1,3→N3}. Code: `Node* lru = tail->prev; remove(lru); keyMap.erase(lru->key); delete lru; Node* n = new Node(3,3); addToHead(n); keyMap[3]=n;`

04. Check: get(2)→-1 ✓ (evicted). get(1)→1 ✓. get(3)→3 ✓.

05. Node struct: `struct Node { int key, val; Node *prev, *next; Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {} };` → Hand: N1 at 0xA occupies 24 bytes (2×int + 2×ptr).

06. DLL with dummies: Head=0x0(dummy), Tail=0xF(dummy). Init: H→next=T, T→prev=H. Code: `head = new Node(-1,-1); tail = new Node(-1,-1); head->next = tail; tail->prev = head;`

07. remove(node) → Hand: node=0xA, prev=0x0, next=0xB. 0x0→next=0xB. 0xB→prev=0x0. Node 0xA floating. Code: `node->prev->next = node->next; node->next->prev = node->prev;`

08. addToHead(node) → Hand: node=0xA, head=0x0, oldFirst=0xB. 0xA→next=0xB. 0xB→prev=0xA. 0x0→next=0xA. 0xA→prev=0x0. Result: 0x0⇄0xA⇄0xB⇄0xF. Code: `node->next = head->next; head->next->prev = node; head->next = node; node->prev = head;`

09. moveToHead(node) → remove(node) + addToHead(node). ∴ Two calls. Code: `remove(node); addToHead(node);`

10. F1: remove() on head→next when only 1 element? → Hand: [H]⇄[N1]⇄[T]. N1→prev=H, N1→next=T. H→next=T, T→prev=H. Works ✓. No special case.

11. F2: addToHead() when list empty? → Hand: [H]⇄[T]. oldFirst=T. node→next=T. T→prev=node. H→next=node. node→prev=H. [H]⇄[node]⇄[T]. Works ✓. No special case.

12. F3: put() on existing key? → Hand: key=1 exists. node=map[1]. node→val=newVal. moveToHead(node). Do NOT size++. Do NOT evict. Code: `if (keyMap.count(key)) { Node* n = keyMap[key]; n->val = val; moveToHead(n); return; }`

13. F4: get() on missing key? → Hand: map.count(key)==0 → return -1. No state change. Code: `if (!keyMap.count(key)) return -1;`

14. C=1 trace: put(1,10) → [H]⇄[N1]⇄[T]. Map{1→N1}. sz=1. put(2,20) → sz=1=C, evict N1 (tail→prev). [H]⇄[N2]⇄[T]. Map{2→N2}. get(1)→-1 ✓. get(2)→20 ✓.

15. Addr trace C=2: H=0x0, T=0xF, N1=0xA, N2=0xB, N3=0xC. Init: 0x0→next=0xF, 0xF→prev=0x0. put(1,1): 0x0→0xA→0xF. Map{1:0xA}. put(2,2): 0x0→0xB→0xA→0xF. Map{1:0xA,2:0xB}. get(1): remove 0xA → 0x0→0xB→0xF. add 0xA → 0x0→0xA→0xB→0xF. put(3,3): evict 0xB → 0x0→0xA→0xF. add 0xC → 0x0→0xC→0xA→0xF. Map{1:0xA,3:0xC}.

16. Complexity: get() → map.find O(1) + remove O(1) + addToHead O(1) = O(1). put() → same + evict O(1) = O(1). Space = O(C) nodes + O(C) map entries.

17. Class skeleton: `class LRUCache { int cap, sz; unordered_map<int, Node*> keyMap; Node *head, *tail; void remove(Node*); void addToHead(Node*); void moveToHead(Node*); public: LRUCache(int c); int get(int k); void put(int k, int v); void clear(); };`

---
Self-Check:
- Line 06: Dummy nodes derived from "avoid null checks in remove/add".
- Line 09: moveToHead = remove + add derived from "can't just point head to middle".
- Line 15: Full pointer trace with real addresses.
- No jumps. Each step uses previous state.

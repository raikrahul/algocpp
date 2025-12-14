# T9 Predictive Text

## Problem Statement
```
2→ABC  3→DEF  4→GHI  5→JKL  6→MNO  7→PQRS  8→TUV  9→WXYZ  0→space  1→{,.!?}
```
Input: digit sequence "2665" → Output: {"book","cool",...} ∵ b=2,o=6,o=6,k=5 ∧ c=2,o=6,o=6,l=5

---

01. Write char→digit mapping by hand: a→2,b→2,c→2,d→3,e→3,f→3,g→4,h→4,i→4,j→5,k→5,l→5,m→6,n→6,o→6,p→7,q→7,r→7,s→7,t→8,u→8,v→8,w→9,x→9,y→9,z→9 → total 26 chars → code: `int charToDigit(char c) { return "22233344455566677778889999"[c-'a']-'0'; }` → trace: 'j'-'a'=9 → "..."[9]='5' → 5 ✓
02. Convert "jello" to digits by hand: j→5,e→3,l→5,l→5,o→6 → "53556" → Convert "rocks" to digits: r→7,o→6,c→2,k→5,s→7 → "76257" → Convert "socks" to digits: s→7,o→6,c→2,k→5,s→7 → "76257" → SURPRISE: "rocks"="socks"=76257 → same digit sequence, different words → this is the collision the problem tests → code: `string wordToDigits(string w) { string d; for(char c:w) d+=charToDigit(c)+'0'; return d; }`
03. Draw empty trie root node with 8 children (digits 2-9): `[root]→[2][3][4][5][6][7][8][9]` → each child=nullptr initially → index mapping: digit '2'→index 0, '3'→index 1, ..., '9'→index 7 → code: `int idx = digit - '2';` → trace: '5'-'2'=3 ✓, '7'-'2'=5 ✓
04. Insert "jello"=53556 into empty trie step-by-step: root→children[3]=new node(digit 5, depth 1)→children[1]=new node(digit 3, depth 2)→children[3]=new node(digit 5, depth 3)→children[3]=new node(digit 5, depth 4)→children[4]=new node(digit 6, depth 5, words={"jello"}) → draw: `[root]─5→[n1]─3→[n2]─5→[n3]─5→[n4]─6→[n5:words={"jello"}]` → 5 nodes created, path length = 5 = length("jello") ✓
05. Insert "rocks"=76257 into same trie: root→children[5]=new node(digit 7)→children[4]=new node(digit 6)→children[0]=new node(digit 2)→children[3]=new node(digit 5)→children[5]=new node(digit 7, words={"rocks"}) → draw parallel path: `[root]─7→[r1]─6→[r2]─2→[r3]─5→[r4]─7→[r5:words={"rocks"}]` → no overlap with "jello" path ∵ first digits differ (5≠7) ✓
06. Insert "socks"=76257 into same trie: root→children[5] EXISTS (digit 7)→children[4] EXISTS (digit 6)→children[0] EXISTS (digit 2)→children[3] EXISTS (digit 5)→children[5] EXISTS (digit 7) → node exists WITH words={"rocks"} → APPEND "socks" to linked list → words={"rocks","socks"} → draw: `[r5:words={"rocks"→"socks"}]` → THIS IS THE COLLISION HANDLING → no new nodes created, reused path ✓
07. Trace getAllWords("76257"): start at root → '7'-'2'=5 → children[5]=node(7) ✓ → '6'-'2'=4 → children[4]=node(6) ✓ → '2'-'2'=0 → children[0]=node(2) ✓ → '5'-'2'=3 → children[3]=node(5) ✓ → '7'-'2'=5 → children[5]=node(7) ✓ → reached end, return words={"rocks","socks"} → O(k) where k=5=length of digit sequence ✓
08. Trace getAllWords("53556"): start at root → '5'-'2'=3 → children[3]=node(5) ✓ → '3'-'2'=1 → children[1]=node(3) ✓ → '5'-'2'=3 → children[3]=node(5) ✓ → '5'-'2'=3 → children[3]=node(5) ✓ → '6'-'2'=4 → children[4]=node(6) ✓ → reached end, return words={"jello"} → single word, no collision ✓
09. Trace getAllWords("99999"): start at root → '9'-'2'=7 → children[7]=nullptr → return {} empty list → no words in dictionary match this sequence → O(1) early termination ✓
10. Calculate memory for trie node: 8 children pointers × 8 bytes = 64 bytes + vector<string> words overhead ≈ 24 bytes + string data → per node ≈ 88 bytes minimum → dictionary with 10000 words, average length 5 → worst case 10000×5=50000 nodes → 50000×88=4.4MB → realistic: shared prefixes reduce by ~60% → ~1.8MB ✓
11. Calculate insertion complexity: word length = k → k node traversals/creations → O(k) per word → n words → O(n×k_avg) total → k_avg ≈ 5 → 10000 words → 50000 operations ✓
12. Test case "22737"→{acres,bards,barer,bares,barfs,baser,bases,caper,capes,cards,carer,cares,cases}: convert each word by hand → a=2,c=2,r=7,e=3,s=7 → "acres"=22737 ✓ → b=2,a=2,r=7,d=3,s=7 → "bards"=22737 ✓ → ALL 13 words map to 22737 → linked list at terminal node has 13 entries
13. Test case "46637"→{goner,goods,goofs,homer,homes,honer,hones,hoods,hoofs,inner}: g=4,o=6,n=6,e=3,r=7 → "goner"=46637 ✓ → h=4,o=6,m=6,e=3,r=7 → "homer"=46637 ✓ → i=4,n=6,n=6,e=3,r=7 → "inner"=46637 ✓ → 10 collisions at same node
14. Constructor pseudocode: read dictionary file line by line → for each word: convert to digit sequence → traverse/create trie path → at terminal node, append word to linked list → code structure: `T9Prediction(string filename) { ifstream f(filename); string word; while(f>>word) { string digits=wordToDigits(word); insertIntoTrie(digits,word); } }`
15. Node structure: `struct Node { Node* children[8]; vector<string> words; Node() { fill(children,children+8,nullptr); } };` → children[0]=digit 2, children[7]=digit 9 → words vector stores collision list
16. Edge case N=0: empty dictionary → root has all nullptr children → getAllWords("anything") returns {} → O(1) ✓
17. Edge case single char: getAllWords("2") → traverse 1 level → return words at depth 1 that are single letters {a,b,c} if in dictionary
18. Edge case "0": digit 0 = space → not in children[0-7] range → need special handling OR reject → problem says 0=space, 1=symbols → these are word separators, not part of word sequences → getAllWords should handle only 2-9
19. Memory leak prevention: destructor must delete all nodes → post-order traversal: `void deleteNode(Node* n) { if(!n) return; for(int i=0;i<8;i++) deleteNode(n->children[i]); delete n; }` → call deleteNode(root) in destructor

---

## FAILURE PREDICTIONS

F1. OFF-BY-ONE in index: digit '2' should map to index 0, not index 2 → `children[digit-'2']` not `children[digit-'0']` → digit='5' → '5'-'2'=3 ✓ vs '5'-'0'=5 ✗ (out of bounds for 8-element array)
F2. FORGOT to check nullptr before traversal: getAllWords traverses children[idx] without checking if nullptr → segfault → must check `if(!current->children[idx]) return {};`
F3. APPENDED word to wrong node: inserted word at intermediate node instead of terminal node → only append at node corresponding to LAST digit of sequence
F4. RETURNED copy instead of reference: `vector<string> getAllWords()` returns copy, `vector<string>& getAllWords()` returns reference → copy = O(n) overhead, reference = O(1) but unsafe if trie modified → choose based on use case
F5. FORGOT linked list / used single string: node.word instead of node.words → loses all collisions except last inserted word → "rocks" overwrites "socks" or vice versa
F6. CASE SENSITIVITY: dictionary has "Book" vs "book" → 'B'-'a' = negative index → must lowercase: `char c = tolower(word[i]);` before charToDigit
F7. INVALID CHARS: dictionary word contains hyphen "self-aware" or apostrophe "don't" → these don't map to 2-9 → must skip or reject → `if(c<'a'||c>'z') continue;` or reject entire word
F8. MEMORY LEAK: no destructor → nodes allocated with new but never deleted → implement ~T9Prediction() with recursive delete
F9. WRONG charToDigit formula: tried arithmetic `(c-'a')/3+2` → fails for 7(pqrs=4 chars) and 9(wxyz=4 chars) → 'p'-'a'=15, 15/3=5, 5+2=7 ✓ but 's'-'a'=18, 18/3=6, 6+2=8 ✗ (should be 7) → use lookup table instead
F10. EMPTY STRING input: getAllWords("") → no digits → should return {} or root.words (if any) → edge case to handle
F11. DUPLICATE WORDS in dictionary: "book" appears twice → appended twice to words vector → {book,book} → should check `if(words.empty()||words.back()!=word) words.push_back(word);` OR use set
F12. PREFIX CONFUSION: "go"=46 and "gone"=4663 → "go" stored at depth 2, "gone" stored at depth 4 → getAllWords("46") returns {"go"}, getAllWords("4663") returns {"gone"} → intermediate nodes CAN have words if shorter dictionary words exist

---

# MISTAKES MADE

M1. LINE 23 → `return c-'a';` → WRONG: returns 0..25 (alphabet index) not 2..9 (phone digit) → SHOULD BE: switch statement or lookup table returning 2-9 → SLOPPY: confused "position in alphabet" with "phone key number" → MISSED: function name says "ToDigit" meaning phone digit → PREVENT: trace one example by hand before coding: 'r'-'a'=17 ≠ 7

M2. LINE 69 → `digits += charToDigit(c);` → WRONG: int 7 appended as ASCII 0x07 (bell char) not '7' → SHOULD BE: `digits += ('0' + charToDigit(c));` → SLOPPY: forgot int→char conversion → MISSED: int 7 ≠ char '7' = ASCII 55 → PREVENT: trace: charToDigit('r')=7, string += 7 → string contains 0x07 not 0x37

M3. LINE 60 → switch has no default case → WARNING: "non-void function does not return a value in all control paths" → SHOULD BE: `default: return 0;` → SLOPPY: assumed only a-z passed → MISSED: uppercase, digits, symbols can crash → PREVENT: always add default case in switch

M4. LINE 90-93 → deleteNode not implemented → WRONG: memory leak, destructor calls empty function → SHOULD BE: recursive post-order delete → SLOPPY: left boilerplate unchanged → MISSED: ~T9Prediction() calls deleteNode(root) but deleteNode does nothing → PREVENT: implement destructor logic or remove destructor call

---

# WHY SLOPPY

Q1. M1: Did you trace 'r'→? before writing `return c-'a';`? → NO → brain skipped step
Q2. M2: Did you check what `string += int` does? → NO → assumed automatic conversion
Q3. M3: Did you consider non-lowercase input? → NO → tunnel vision on happy path
Q4. M4: Did you run valgrind to check memory leaks? → NO → ignored destructor responsibility


01. Draw 2 boxes labeled map₁ and map₂, map₁ stores key→value, map₂ stores value→key, draw map₁={} map₂={} both empty at start, ∴ getByKey(x)=∅ and getByValue(x)=∅ for all x because both maps contain 0 entries → `std::unordered_map<K,V> key_to_value; std::unordered_map<V,K> value_to_key;`
02. put("google.com","142.250.185.14") → write "google.com" as key in map₁, write "142.250.185.14" as value next to it, draw arrow from key to value, now map₁={google.com→142.250.185.14}, count entries in map₁ = 1, for map₂ do reverse: write "142.250.185.14" as key, write "google.com" as value, draw map₂={142.250.185.14→google.com}, count = 1, ∴ map₁.size()=map₂.size()=1 ✓ → `key_to_value["google.com"]="142.250.185.14"; value_to_key["142.250.185.14"]="google.com";`
03. getByKey("google.com") → scan map₁ for key "google.com", found at position 0, read value = "142.250.185.14", return "142.250.185.14", time = O(1) because hash lookup, did NOT scan map₂ at all → `auto it=key_to_value.find("google.com"); if(it!=key_to_value.end()) return it->second;`
04. getByValue("142.250.185.14") → if map₂ did NOT exist: scan ALL entries in map₁, compare each value with "142.250.185.14", at N=1000000 entries this = 1000000 comparisons = O(N) = slow, but map₂ EXISTS ∴ scan map₂ for key "142.250.185.14", found at position 0, read value = "google.com", return "google.com", time = O(1) → `auto it=value_to_key.find("142.250.185.14"); if(it!=value_to_key.end()) return it->second;`
05. put("github.com","140.82.121.4") → map₁ currently has 1 entry, add new entry: map₁={google.com→142.250.185.14, github.com→140.82.121.4}, count = 2, map₂ add: map₂={142.250.185.14→google.com, 140.82.121.4→github.com}, count = 2, verify map₁.size()=map₂.size()=2 ✓
06. put("google.com","172.217.14.206") → key "google.com" EXISTS in map₁, read old_value = map₁["google.com"] = "142.250.185.14", this old_value "142.250.185.14" must be ERASED from map₂ otherwise getByValue("142.250.185.14") returns "google.com" but "google.com" now maps to "172.217.14.206" = STALE DATA ✗, erase map₂["142.250.185.14"], map₂={140.82.121.4→github.com}, update map₁["google.com"]="172.217.14.206", insert map₂["172.217.14.206"]="google.com", final: map₁={google.com→172.217.14.206, github.com→140.82.121.4}, map₂={140.82.121.4→github.com, 172.217.14.206→google.com} → `auto it=key_to_value.find(key); if(it!=key_to_value.end()){ value_to_key.erase(it->second); } key_to_value[key]=value; value_to_key[value]=key;`
07. F1: Forgot to erase old_value from map₂ → put(A,100) gives map₂={100→A}, put(A,200) gives map₁={A→200} but map₂={100→A, 200→A}, now getByValue(100) returns A ✗ but A maps to 200 not 100, expected: getByValue(100)=∅ because no key maps to 100, actual: getByValue(100)=A → WRONG
08. put("dns.alt","140.82.121.4") → value "140.82.121.4" EXISTS in map₂, read old_key = map₂["140.82.121.4"] = "github.com", this old_key must be ERASED from map₁ otherwise getByKey("github.com") returns "140.82.121.4" but "140.82.121.4" now maps to "dns.alt" = BIJECTION VIOLATED, erase map₁["github.com"], map₁={google.com→172.217.14.206}, update map₁["dns.alt"]="140.82.121.4", update map₂["140.82.121.4"]="dns.alt", final: map₁={google.com→172.217.14.206, dns.alt→140.82.121.4}, map₂={172.217.14.206→google.com, 140.82.121.4→dns.alt} → `auto it=value_to_key.find(value); if(it!=value_to_key.end()){ key_to_value.erase(it->second); } key_to_value[key]=value; value_to_key[value]=key;`
09. F2: Forgot to erase old_key from map₁ when value collides → put(A,100) gives map₁={A→100}, put(B,100) gives map₂={100→B} but map₁={A→100, B→100}, now getByKey(A) returns 100 ✗ but value 100 belongs to B only in bijection, expected: getByKey(A)=∅, actual: getByKey(A)=100 → WRONG
10. Complete put(key,value) algorithm: step1 check if key exists in map₁ → if yes erase old_value from map₂, step2 check if value exists in map₂ → if yes erase old_key from map₁, step3 insert key_to_value[key]=value, step4 insert value_to_key[value]=key, each step = O(1), total = O(1) → `void put(const K& key, const V& value){ auto kit=key_to_value.find(key); if(kit!=key_to_value.end()) value_to_key.erase(kit->second); auto vit=value_to_key.find(value); if(vit!=value_to_key.end()) key_to_value.erase(vit->second); key_to_value[key]=value; value_to_key[value]=key; }`
11. removeByKey("google.com") → find "google.com" in map₁, it=map₁.find("google.com"), if it≠end then read value=it->second="172.217.14.206", erase map₂["172.217.14.206"], erase map₁["google.com"], count before = 2, count after = 1, verify map₁.size()=map₂.size()=1 ✓ → `void removeByKey(const K& key){ auto it=key_to_value.find(key); if(it!=key_to_value.end()){ value_to_key.erase(it->second); key_to_value.erase(it); } }`
12. F3: removeByKey forgot to erase from map₂ → removeByKey(A) erases map₁[A] but map₂[100]=A remains, getByValue(100) returns A ✗ but A deleted, expected: getByValue(100)=∅, actual: getByValue(100)=A → STALE POINTER
13. removeByValue("140.82.121.4") → find "140.82.121.4" in map₂, it=map₂.find("140.82.121.4"), if it≠end then read key=it->second="dns.alt", erase map₁["dns.alt"], erase map₂["140.82.121.4"], count = 0 → `void removeByValue(const V& value){ auto it=value_to_key.find(value); if(it!=value_to_key.end()){ key_to_value.erase(it->second); value_to_key.erase(it); } }`
14. N=0 edge case: map₁={} map₂={}, getByKey(any)=∅, getByValue(any)=∅, containsKey(any)=✗, containsValue(any)=✗, size()=0, no crash on empty maps ✓
15. N=1 edge case: put(42,"answer") → map₁={42→answer} map₂={answer→42}, getByKey(42)="answer" ✓, getByValue("answer")=42 ✓, getByKey(0)=∅ ✓, removeByKey(42) → map₁={} map₂={} ✓
16. Memory calculation: each entry stored twice, entry_size = sizeof(K) + sizeof(V) + hash_overhead ≈ 32 bytes, 2 maps × N entries × 32 bytes = 64N bytes, at N=1000000: 64×10⁶ = 64MB, at N=10000000: 640MB
17. Time calculation: put = 2 finds + 0-2 erases + 2 inserts = O(1) amortized, getByKey = 1 find = O(1), getByValue = 1 find = O(1), removeByKey = 1 find + 2 erases = O(1), removeByValue = 1 find + 2 erases = O(1)
18. Hash collision worst case: all N keys hash to same bucket, lookup = O(N) linear scan in bucket, probability at good hash function ≈ 0, rehash at load_factor=0.75 triggers bucket doubling, amortized O(1) maintained
19. DNS forward lookup: getByKey("google.com") → "142.250.185.14", DNS reverse lookup (PTR record): getByValue("142.250.185.14") → "google.com", both O(1), single map approach: forward O(1), reverse O(N) scan all entries → 2-map design = correct
20. Sequence trace: put(1,100) → map₁={1→100} map₂={100→1} | put(2,200) → map₁={1→100,2→200} map₂={100→1,200→2} | put(1,300) → old=100, erase map₂[100], map₁={1→300,2→200} map₂={200→2,300→1} | put(3,200) → old_key=2, erase map₁[2], map₁={1→300,3→200} map₂={300→1,200→3} | getByKey(1)=300 ✓ | getByKey(2)=∅ ✓ | getByValue(100)=∅ ✓ | getByValue(200)=3 ✓
21. Invariant check after each operation: map₁.size() must equal map₂.size(), for each (k,v) in map₁ there exists (v,k) in map₂, for each (v,k) in map₂ there exists (k,v) in map₁, violation of invariant = bug in put/remove logic

---

SELF-CHECK:
- Line 01: Introduced map₁ and map₂ from problem requirement (bidirectional lookup), derived from O(1) getByValue need.
- Line 06: Derived erase logic from stale data observation, not introduced without reason.
- Line 08: Derived value collision handling from bijection requirement.
- Line 10: Combined all put steps, each step previously derived in 02, 06, 08.
- No new variables introduced without prior calculation.
- No memorization required, each step shows concrete data.
- All failures (F1, F2, F3) derived from "what if forgot X" scenarios run by hand.

---

ERROR REPORT (2025-12-12):

E1. LINE 43 → value_to_key(value) → WRONG SYNTAX → value_to_key[...] with brackets not parentheses
→ SLOPPY: confused function call () with map access []
→ MISSED: unordered_map uses operator[] or .find(), not operator()
→ PREVENT: map access = [], function call = ()

E2. LINE 43 → value_to_key(value) → WRONG MAP → should read from key_to_value[key]
→ TRACE: put("A","100") then put("A","200"), key "A" exists, need old_val
→ YOUR CODE: old_val = value_to_key["200"] → "200" NOT IN map₂ yet → undefined
→ CORRECT: old_val = key_to_value["A"] = "100" → this is the value to erase from map₂
→ SLOPPY: did not trace which map holds which data
→ MISSED: key exists in map₁ ∴ old_val = map₁[key], not map₂[value]
→ PREVENT: draw arrow direction before writing code: key→value in map₁, value→key in map₂

E3. LINE 49 → key_to_value(key) → WRONG MAP → should read from value_to_key[value]
→ TRACE: put("A","100") then put("B","100"), value "100" exists in map₂, need old_key
→ YOUR CODE: old_key = key_to_value["B"] → "B" NOT IN map₁ yet → undefined
→ CORRECT: old_key = value_to_key["100"] = "A" → this is the key to erase from map₁
→ SLOPPY: copy-paste error, did not think which map to query
→ MISSED: value exists in map₂ ∴ old_key = map₂[value], not map₁[key]
→ PREVENT: before each erase, ask "WHERE is the thing I want to find?" map₁ has keys, map₂ has values

E4. LINE 82 → auto it = value_to_key.find(value); return std::nullopt; → MISSING RETURN BRANCH
→ YOUR CODE: found iterator but did not return it->second
→ CORRECT: if(it != value_to_key.end()) return it->second; return std::nullopt;
→ SLOPPY: wrote declaration, forgot to use it
→ MISSED: copy-paste from getByKey but deleted the if-statement
→ PREVENT: after writing .find(), always write if(it!=end) return it->second on same line

PATTERN DETECTED:
- E2 and E3: confused source map with destination map
- ROOT: did not trace data flow with arrows before coding
- FIX: always draw map₁[key]→value, map₂[value]→key, then read code from drawing

ORTHOGONAL THOUGHTS:
- Brain wrote value_to_key(value) → thinking "I need old value, value_to_key has values" → WRONG
- Correct thinking: "key exists in key_to_value, key_to_value[key] gives old_value"
- Brain skipped step: "which map do I query to get old_value?"
- Brain jumped to: "value_to_key sounds related to value"
- Name similarity caused confusion: value_to_key ≠ "get value", it means "given value, get key"

QUESTIONS TO ASK BEFORE EACH LINE:
Q1. What do I need? (old_val or old_key)
Q2. Where is it stored? (map₁ for key→value, map₂ for value→key)
Q3. What do I already have? (key or value from function parameter)
Q4. How do I get what I need from what I have?

TRACE FOR E2 FIX:
- Need: old_val (the value currently mapped to this key)
- Stored: map₁ = key_to_value (stores key→value pairs)
- Have: key (from function parameter)
- Get: key_to_value[key] = old_val ✓

TRACE FOR E3 FIX:
- Need: old_key (the key currently mapped to this value)
- Stored: map₂ = value_to_key (stores value→key pairs)
- Have: value (from function parameter)
- Get: value_to_key[value] = old_key ✓

---

E5. TEST LINE 296 → assert(!bm.getByValue(i*10).has_value()) → TEST LOGIC WRONG
→ TRACE: initial put(i, i*10) for i=0..9999, overwrite put(i, i*100) for i=0..4999
→ i=10: old_val=10×10=100, new_val=10×100=1000
→ i=1: old_val=1×10=10, new_val=1×100=100
→ After put(10,1000): map₂[100] erased (was 10's old value)
→ After put(1,100): map₂[100]=1 inserted (1's new value)
→ getByValue(100) returns 1, NOT nullopt
→ TEST EXPECTED: getByValue(100)=nullopt (old value of key 10)
→ BUT: getByValue(100)=1 (new value of key 1)
→ ROOT: old values (i×10) and new values (i×100) OVERLAP for i≥10 vs i≥1
→ 10×10=100=1×100, 20×10=200=2×100, ..., 90×10=900=9×100
→ FIX: use non-overlapping scheme: old=i×2 (even), new=i×2+1 (odd)
→ LESSON: when testing overwrite, ensure old and new value sets are DISJOINT

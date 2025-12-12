#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>
#include <cassert>

// TWO MAPS: map₁[key]=value, map₂[value]=key
// put(k,v): O(1) amortized
// getByKey(k): O(1)
// getByValue(v): O(1)
// SPACE: 2×N entries

template <typename K, typename V>
class BiMap {
private:
    std::unordered_map<K, V> key_to_value;   // map₁
    std::unordered_map<V, K> value_to_key;   // map₂

public:
    // put(google.com, 142.250.185.14)
    // → key_to_value[google.com] = 142.250.185.14
    // → value_to_key[142.250.185.14] = google.com
    //
    // CASE 1: new key, new value → insert both
    // CASE 2: existing key, new value → erase old_value from map₂, update both
    // CASE 3: new key, existing value → erase old_key from map₁, update both
    // CASE 4: existing key, existing value (same pair) → no-op
    //
    // Example numeric trace:
    // put(1, 100): key_to_value={1→100}, value_to_key={100→1}
    // put(1, 200): old_val=100, erase(100) from map₂, key_to_value={1→200}, value_to_key={200→1}
    // put(2, 200): old_key=1, erase(1) from map₁, key_to_value={2→200}, value_to_key={200→2}
    void put(const K& key, const V& value) {
        // TODO: implement
        // Step 1: check if key exists in key_to_value
        //         if yes → old_val = key_to_value[key] → value_to_key.erase(old_val)
        // Step 2: check if value exists in value_to_key
        //         if yes → old_key = value_to_key[value] → key_to_value.erase(old_key)
        // Step 3: key_to_value[key] = value
        // Step 4: value_to_key[value] = key
        if ( key_to_value.find(key) != key_to_value.end())
        {
            auto old_val = key_to_value[key];
            value_to_key.erase(old_val);
        }

        if (value_to_key.find(value) != value_to_key.end())
        {
            auto old_key = value_to_key[value];
            key_to_value.erase(old_key);
        }

        key_to_value[key] = value;
        value_to_key[value] = key;
    }

    // getByKey(google.com) → key_to_value.find(google.com)
    // → found: return 142.250.185.14
    // → not found: return std::nullopt
    //
    // Time: O(1) average
    std::optional<V> getByKey(const K& key) const {
        // TODO: implement
        // auto it = key_to_value.find(key);
        // if (it != key_to_value.end()) return it->second;
        // return std::nullopt;
        auto it = key_to_value.find(key);
        if (it != key_to_value.end()) return it->second;
        return std::nullopt;
    }

    // getByValue(142.250.185.14) → value_to_key.find(142.250.185.14)
    // → found: return google.com
    // → not found: return std::nullopt
    //
    // Time: O(1) average
    // THIS IS THE WHOLE POINT: without map₂, this would be O(N) scan
    std::optional<K> getByValue(const V& value) const {
        // TODO: implement
        // auto it = value_to_key.find(value);
        // if (it != value_to_key.end()) return it->second;
        // return std::nullopt;
        auto it = value_to_key.find(value);
        if (it != value_to_key.end()) return it->second;
        return std::nullopt;
    }

    // containsKey: O(1)
    bool containsKey(const K& key) const {
        return key_to_value.find(key) != key_to_value.end();
    }

    // containsValue: O(1) with map₂
    // O(N) scan without map₂
    bool containsValue(const V& value) const {
        return value_to_key.find(value) != value_to_key.end();
    }

    // size: returns number of key-value pairs
    // map₁.size() == map₂.size() always (invariant)
    size_t size() const {
        return key_to_value.size();
    }

    // removeByKey(k): O(1)
    // → find value, erase from both maps
    void removeByKey(const K& key) {
        // TODO: implement
        // auto it = key_to_value.find(key);
        // if (it != key_to_value.end()) {
        //     value_to_key.erase(it->second);
        //     key_to_value.erase(it);
        // }
        auto it = key_to_value.find(key);
        if (it != key_to_value.end()) {
            value_to_key.erase(it->second);
            key_to_value.erase(it);
        }   
    }

    // removeByValue(v): O(1)
    // → find key, erase from both maps
    void removeByValue(const V& value) {
        // TODO: implement
        // auto it = value_to_key.find(value);
        // if (it != value_to_key.end()) {
        //     key_to_value.erase(it->second);
        //     value_to_key.erase(it);
        // }
        auto it = value_to_key.find(value);
        if (it != value_to_key.end()) {
            key_to_value.erase(it->second);
            value_to_key.erase(it);
        }   
    }
};

// test_dns: domain↔IP
void test_dns() {
    BiMap<std::string, std::string> dns;
    
    // put(google.com, 142.250.185.14)
    // key_to_value: {google.com → 142.250.185.14}
    // value_to_key: {142.250.185.14 → google.com}
    dns.put("google.com", "142.250.185.14");
    dns.put("github.com", "140.82.121.4");
    dns.put("amazon.com", "54.239.28.85");
    
    // forward lookup
    assert(dns.getByKey("google.com").value() == "142.250.185.14");
    assert(dns.getByKey("github.com").value() == "140.82.121.4");
    
    // reverse lookup (DNS ptr record)
    assert(dns.getByValue("142.250.185.14").value() == "google.com");
    assert(dns.getByValue("140.82.121.4").value() == "github.com");
    
    // not found
    assert(!dns.getByKey("notexist.com").has_value());
    assert(!dns.getByValue("1.2.3.4").has_value());
}

// test_overwrite_key: put(k,v1) then put(k,v2)
void test_overwrite_key() {
    BiMap<int, int> bm;
    
    // put(1, 100): map₁={1→100}, map₂={100→1}
    bm.put(1, 100);
    assert(bm.getByKey(1).value() == 100);
    assert(bm.getByValue(100).value() == 1);
    
    // put(1, 200): erase 100 from map₂, map₁={1→200}, map₂={200→1}
    bm.put(1, 200);
    assert(bm.getByKey(1).value() == 200);
    assert(bm.getByValue(200).value() == 1);
    
    // old value 100 should not exist in map₂
    assert(!bm.getByValue(100).has_value());
    
    assert(bm.size() == 1);
}

// test_overwrite_value: put(k1,v) then put(k2,v)
void test_overwrite_value() {
    BiMap<int, int> bm;
    
    // put(1, 100): map₁={1→100}, map₂={100→1}
    bm.put(1, 100);
    
    // put(2, 100): value collision → erase key 1 from map₁
    // map₁={2→100}, map₂={100→2}
    bm.put(2, 100);
    
    assert(!bm.getByKey(1).has_value());  // key 1 removed
    assert(bm.getByKey(2).value() == 100);
    assert(bm.getByValue(100).value() == 2);
    
    assert(bm.size() == 1);
}

// test_empty: N=0
void test_empty() {
    BiMap<std::string, std::string> bm;
    
    assert(bm.size() == 0);
    assert(!bm.getByKey("any").has_value());
    assert(!bm.getByValue("any").has_value());
    assert(!bm.containsKey("any"));
    assert(!bm.containsValue("any"));
}

// test_single: N=1
void test_single() {
    BiMap<int, std::string> bm;
    
    bm.put(42, "answer");
    
    assert(bm.size() == 1);
    assert(bm.getByKey(42).value() == "answer");
    assert(bm.getByValue("answer").value() == 42);
    assert(bm.containsKey(42));
    assert(bm.containsValue("answer"));
    assert(!bm.containsKey(0));
    assert(!bm.containsValue("question"));
}

// test_remove_by_key
void test_remove_by_key() {
    BiMap<int, int> bm;
    
    bm.put(1, 100);
    bm.put(2, 200);
    
    // remove key 1 → both maps should not contain 1 or 100
    bm.removeByKey(1);
    
    assert(!bm.getByKey(1).has_value());
    assert(!bm.getByValue(100).has_value());
    assert(bm.getByKey(2).value() == 200);
    assert(bm.size() == 1);
}

// test_remove_by_value
void test_remove_by_value() {
    BiMap<int, int> bm;
    
    bm.put(1, 100);
    bm.put(2, 200);
    
    // remove value 200 → both maps should not contain 2 or 200
    bm.removeByValue(200);
    
    assert(!bm.getByKey(2).has_value());
    assert(!bm.getByValue(200).has_value());
    assert(bm.getByKey(1).value() == 100);
    assert(bm.size() == 1);
}

// test_same_key_value_type: key and value both strings
void test_same_key_value_type() {
    BiMap<std::string, std::string> bm;
    
    bm.put("key1", "value1");
    bm.put("key2", "value2");
    
    // key="192.168.1.1", value="192.168.1.1" → same string
    bm.put("192.168.1.1", "192.168.1.1");
    
    assert(bm.getByKey("192.168.1.1").value() == "192.168.1.1");
    assert(bm.getByValue("192.168.1.1").value() == "192.168.1.1");
}

// test_large: N=10000
void test_large() {
    BiMap<int, int> bm;
    
    // put 10000 pairs: (0,0), (1,2), (2,4), ..., (9999,19998)
    // using i*2 to avoid collision with new values
    for (int i = 0; i < 10000; i++) {
        bm.put(i, i * 2);
    }
    
    assert(bm.size() == 10000);
    
    // verify all
    for (int i = 0; i < 10000; i++) {
        assert(bm.getByKey(i).value() == i * 2);
        assert(bm.getByValue(i * 2).value() == i);
    }
    
    // overwrite half with odd values: (0,1), (1,3), (2,5), ..., (4999,9999)
    // new value = i*2+1, old value = i*2, no overlap
    for (int i = 0; i < 5000; i++) {
        bm.put(i, i * 2 + 1);  // change from even to odd
    }
    
    // old values 0,2,4,...,9998 (even) for keys 0-4999 should not exist
    // new values 1,3,5,...,9999 (odd) should exist
    for (int i = 0; i < 5000; i++) {
        assert(!bm.getByValue(i * 2).has_value());  // old even value gone
        assert(bm.getByValue(i * 2 + 1).value() == i);  // new odd value exists
    }
    
    // keys 5000-9999 should still have old even values
    for (int i = 5000; i < 10000; i++) {
        assert(bm.getByKey(i).value() == i * 2);
    }
}

// test_sequence: multiple operations
void test_sequence() {
    BiMap<int, int> bm;
    
    // #01. put(1,100)
    bm.put(1, 100);
    assert(bm.size() == 1);
    
    // #02. put(2,200)
    bm.put(2, 200);
    assert(bm.size() == 2);
    
    // #03. put(1,300) → overwrite key
    bm.put(1, 300);
    assert(bm.size() == 2);
    assert(bm.getByKey(1).value() == 300);
    assert(!bm.getByValue(100).has_value());
    
    // #04. put(3,200) → overwrite value
    bm.put(3, 200);
    assert(bm.size() == 2);
    assert(!bm.getByKey(2).has_value());
    assert(bm.getByValue(200).value() == 3);
    
    // #05. removeByKey(1)
    bm.removeByKey(1);
    assert(bm.size() == 1);
    assert(!bm.containsKey(1));
    assert(!bm.containsValue(300));
    
    // #06. final state: {3→200}
    assert(bm.getByKey(3).value() == 200);
    assert(bm.getByValue(200).value() == 3);
}

int main() {
    test_dns();
    test_overwrite_key();
    test_overwrite_value();
    test_empty();
    test_single();
    test_remove_by_key();
    test_remove_by_value();
    test_same_key_value_type();
    test_large();
    test_sequence();
    
    std::cout << "All tests passed" << std::endl;
    return 0;
}

#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>
#include <vector>




struct Entry {
    int val;
    int freq;
    std::list<int>::iterator it;
};
class LFUCache {
private:
    int capacity;
    int min_freq;
    std::unordered_map<int, Entry> key_map; 
    std::unordered_map<int, std::list<int>> freq_map;
    
    void touch(int key) {
        // TODO: Increase freq, move node from old freq list to new freq list
        // Steps: (1) get old freq, (2) remove from freq_map[old], (3) freq++, 
        //        (4) add to freq_map[new], (5) update iterator in key_map,
        //        (6) if freq_map[min_freq] is empty AND old_freq == min_freq, min_freq++
        Entry& e = key_map[key];
        int old_freq = e.freq;
        freq_map[old_freq].erase(e.it);
        e.freq++;
        freq_map[e.freq].push_back(key);
        e.it = std::prev(freq_map[e.freq].end());
        if (freq_map[old_freq].empty()) {
            freq_map.erase(old_freq);        // ← ADD THIS LINE
             if (old_freq == min_freq) {
                min_freq++;
            }
        }
    }

    void evict() {  
        // TODO: Remove LRU node from freq_map[min_freq]
        // Steps: (1) get front of freq_map[min_freq], (2) erase from key_map,
        //        (3) pop_front from freq_map[min_freq], (4) decrement size
        auto it = freq_map[min_freq].begin();
        int key = *it;
        key_map.erase(key);
        freq_map[min_freq].pop_front();
        if (freq_map[min_freq].empty()) {
            freq_map.erase(min_freq);
        } 

    }

public:
    LFUCache(int cap) : capacity(cap), min_freq(0) {
        // Capacity must be >= 1 for meaningful cache
    }

    ~LFUCache() {
        clear();
    }

    int get(int key) {
        if (!key_map.count(key)) return -1;
        touch(key);
        return key_map[key].val;
    }

    void put(int key, int value) {
        
        if (key_map.count(key))
        {
            Entry& e = key_map[key];
            
            e.val = value;
            touch(key); 
        }
        else
        {
          if (key_map.size() == (size_t)capacity)
          {
            evict();
          }
          freq_map[1].push_back(key);
          key_map[key] = {value, 1, std::prev(freq_map[1].end())};
          min_freq = 1;
        }
    }

    void clear() {
        // TODO: Clear all maps, reset size and min_freq    
        key_map.clear();
        freq_map.clear();
        min_freq = 0;
    }

    void display() {
        std::cout << "LFU Cache State (minFreq=" << min_freq << "):" << std::endl;
        for (auto& [freq, key_list] : freq_map) {
            std::cout << "  freq=" << freq << ": ";
            for (int k : key_list) {
                std::cout << "(" << k << "," << key_map[k].val << ") ";
            }
            std::cout << std::endl;
        }
    }

    // For testing: returns keys in eviction order (min freq, then LRU within freq)
    std::vector<int> get_eviction_order() {
        std::vector<int> result;
        // TODO: Traverse freq_map from min_freq upward, front to back
        return result;
    }
};

void run_tests() {
    // Test 1: Basic put/get
    {
        LFUCache lfu(2);
        lfu.put(1, 10);
        lfu.put(2, 20);
        assert(lfu.get(1) == 10);
        assert(lfu.get(2) == 20);
        std::cout << "Test 1 Passed: Basic Put/Get" << std::endl;
    }

    // Test 2: Eviction by frequency
    {
        LFUCache lfu(2);
        lfu.put(1, 10);  // freq(1)=1
        lfu.put(2, 20);  // freq(2)=1
        lfu.get(1);      // freq(1)=2, freq(2)=1
        lfu.put(3, 30);  // evict key=2 (minFreq=1, LRU in freq=1 is key=2)
        
        assert(lfu.get(2) == -1); // 2 evicted
        assert(lfu.get(1) == 10); // 1 exists, freq(1)=3
        assert(lfu.get(3) == 30); // 3 exists, freq(3)=2
        std::cout << "Test 2 Passed: Eviction by Frequency" << std::endl;
    }

    // Test 3: Tie-breaker (same freq, evict LRU)
    {
        LFUCache lfu(2);
        lfu.put(1, 10);  // freq(1)=1
        lfu.put(2, 20);  // freq(2)=1
        lfu.get(1);      // freq(1)=2
        lfu.get(2);      // freq(2)=2
        // Both have freq=2. LRU within freq=2 is key=1 (accessed first at freq=2)
        lfu.put(3, 30);  // evict minFreq. minFreq=2. LRU in freq=2 = key=1
        
        assert(lfu.get(1) == -1); // 1 evicted
        assert(lfu.get(2) == 20);
        assert(lfu.get(3) == 30);
        std::cout << "Test 3 Passed: Tie-breaker LRU" << std::endl;
    }

    // Test 4: Update existing key
    {
        LFUCache lfu(2);
        lfu.put(1, 10);  // freq(1)=1
        lfu.put(2, 20);  // freq(2)=1
        lfu.put(1, 100); // update key=1, freq(1)=2
        lfu.put(3, 30);  // evict key=2 (minFreq=1)
        
        assert(lfu.get(1) == 100);
        assert(lfu.get(2) == -1);
        assert(lfu.get(3) == 30);
        std::cout << "Test 4 Passed: Update Existing Key" << std::endl;
    }

    // Test 5: Capacity 1
    {
        LFUCache lfu(1);
        lfu.put(1, 10);
        assert(lfu.get(1) == 10);
        lfu.put(2, 20); // evict 1
        assert(lfu.get(1) == -1);
        assert(lfu.get(2) == 20);
        std::cout << "Test 5 Passed: Capacity 1" << std::endl;
    }

    // Test 6: Clear
    {
        LFUCache lfu(3);
        lfu.put(1, 1);
        lfu.put(2, 2);
        lfu.clear();
        assert(lfu.get(1) == -1);
        assert(lfu.get(2) == -1);
        lfu.put(3, 3);
        assert(lfu.get(3) == 3);
        std::cout << "Test 6 Passed: Clear" << std::endl;
    }

    // Test 7: Multiple accesses, complex eviction
    {
        LFUCache lfu(3);
        lfu.put(1, 10); // freq(1)=1
        lfu.put(2, 20); // freq(2)=1
        lfu.put(3, 30); // freq(3)=1
        lfu.get(1);     // freq(1)=2
        lfu.get(1);     // freq(1)=3
        lfu.get(2);     // freq(2)=2
        // freqs: 1→3, 2→2, 3→1. minFreq=1
        lfu.put(4, 40); // evict key=3 (minFreq=1)
        
        assert(lfu.get(3) == -1);
        assert(lfu.get(1) == 10); // freq(1)=4
        assert(lfu.get(2) == 20); // freq(2)=3
        assert(lfu.get(4) == 40); // freq(4)=2
        std::cout << "Test 7 Passed: Complex Eviction" << std::endl;
    }
}

void test_step_01() {
    // C=3
    LFUCache cache(3);
    
    // ops
    cache.put(1, 10);  // freq[1]=1
    cache.put(2, 20);  // freq[2]=1
    cache.put(3, 30);  // freq[3]=1, size=3=C, full
    cache.get(1);      // freq[1]=2
    cache.get(1);      // freq[1]=3
    cache.put(4, 40);  // evict min freq=1, candidates={2,3}, LRU=2, evict 2
    
    // expected output
    assert(cache.get(2) == -1);  // evicted
    assert(cache.get(1) == 10);  // exists
    assert(cache.get(3) == 30);  // exists
    assert(cache.get(4) == 40);  // exists
    std::cout << "Test Step 01 Passed" << std::endl;
}

int main() {
    run_tests();
    std::cout << "All Tests Passed!" << std::endl;
    return 0;
}

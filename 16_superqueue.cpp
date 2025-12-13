#include <iostream>
#include <deque>
#include <queue>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>

// ═══════════════════════════════════════════════════════════════════════════════
// PROBLEM: SuperQueue with O(1) enqueue, O(1) dequeue, O(1) findmin
// ═══════════════════════════════════════════════════════════════════════════════
// YOUR TASK: Implement the logic inside enqueue(), dequeue(), findmin()
// BOILERPLATE: Class skeleton, test cases, main() are provided
// ═══════════════════════════════════════════════════════════════════════════════

class SuperQueue {
private:
    std::queue<int> q;      // Main queue: stores all elements in FIFO order
                            // Example after ENQUEUE(10,5,20): q = {10, 5, 20}
                            //                                      ↑front    ↑back
    
    std::deque<int> d;      // Auxiliary deque: stores ??? (you derive from worksheet)
                            // Example after ENQUEUE(10,5,20): d = {???, ???}
                            // Property: d is always sorted ??? (ascending/descending)

public:
    // ═══════════════════════════════════════════════════════════════════════════
    // ENQUEUE: Add element x to the queue
    // ═══════════════════════════════════════════════════════════════════════════
    // INPUT:  x = element to add, e.g., x = 10
    // BEFORE: q = {5, 20}, d = {5, 20}
    // AFTER:  q = {5, 20, 10}, d = {???, ???}
    // ═══════════════════════════════════════════════════════════════════════════
    void enqueue(int x) {
        // Step 1: Push x to main queue q
        // YOUR CODE: ___________________________________
        q.push(x);
        
        // Step 2: Remove useless elements from d (refer to worksheet step 15-16)
        // YOUR CODE: while (___________________________________) {
        //                ___________________________________
        //            }
       
       while ( d.size() > 0 && x < d.back()  ) 
       {
            d.pop_back();
       }
        
        // Step 3: Push x to d
        // YOUR CODE: ___________________________________
        d.push_back(x);
        
    }

    // ═══════════════════════════════════════════════════════════════════════════
    // DEQUEUE: Remove element from front of queue
    // ═══════════════════════════════════════════════════════════════════════════
    // BEFORE: q = {10, 5, 20}, d = {5, 20}
    // AFTER:  q = {5, 20}, d = {???, ???}
    // ═══════════════════════════════════════════════════════════════════════════
    void dequeue() {
        // Step 1: Check if element leaving q is the current min (refer to worksheet step 21-23)
        // YOUR CODE: if (___________________________________) {
        //                ___________________________________
        //            }
       
        if ( q.front() == d.front())
        {
            d.pop_front();
        }
        // Step 2: Remove front element from q
        // YOUR CODE: ___________________________________
        q.pop();
    }

    // ═══════════════════════════════════════════════════════════════════════════
    // FINDMIN: Return minimum element in queue
    // ═══════════════════════════════════════════════════════════════════════════
    // STATE: q = {10, 5, 20}, d = {5, 20}
    // OUTPUT: 5 (minimum of {10, 5, 20})
    // ═══════════════════════════════════════════════════════════════════════════
    int findmin() const {
        // Edge case: what if queue is empty? (refer to worksheet step 28)
        if (d.empty()) {
            throw std::runtime_error("findmin on empty queue");
        }
        
        // Return minimum (refer to worksheet step 18)
        return d.front();
    }

    // ═══════════════════════════════════════════════════════════════════════════
    // HELPER: Check if queue is empty
    // ═══════════════════════════════════════════════════════════════════════════
    bool empty() const {
        return q.empty();
    }

    // ═══════════════════════════════════════════════════════════════════════════
    // DEBUG: Print current state of q and d
    // ═══════════════════════════════════════════════════════════════════════════
    void debug() const {
        std::cout << "q: [";
        std::queue<int> temp = q;
        while (!temp.empty()) {
            std::cout << temp.front();
            temp.pop();
            if (!temp.empty()) std::cout << ", ";
        }
        std::cout << "]  d: [";
        for (size_t i = 0; i < d.size(); ++i) {
            std::cout << d[i];
            if (i + 1 < d.size()) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// ═══════════════════════════════════════════════════════════════════════════════
// TEST CASES
// ═══════════════════════════════════════════════════════════════════════════════

void test_basic() {
    std::cout << "=== TEST BASIC ===" << std::endl;
    SuperQueue sq;
    
    sq.enqueue(10); sq.debug();  // Expected: q: [10]  d: [10]
    sq.enqueue(5);  sq.debug();  // Expected: q: [10, 5]  d: [5]
    sq.enqueue(20); sq.debug();  // Expected: q: [10, 5, 20]  d: [5, 20]
    
    assert(sq.findmin() == 5);
    std::cout << "findmin() = " << sq.findmin() << " (expected 5)" << std::endl;
    
    sq.dequeue(); sq.debug();    // Expected: q: [5, 20]  d: [5, 20]
    assert(sq.findmin() == 5);
    
    sq.dequeue(); sq.debug();    // Expected: q: [20]  d: [20]
    assert(sq.findmin() == 20);
    
    std::cout << "test_basic PASSED" << std::endl << std::endl;
}

void test_decreasing() {
    std::cout << "=== TEST DECREASING INPUT ===" << std::endl;
    SuperQueue sq;
    
    sq.enqueue(5); sq.debug();   // d: [5]
    sq.enqueue(4); sq.debug();   // d: [4]  (5 killed)
    sq.enqueue(3); sq.debug();   // d: [3]  (4 killed)
    sq.enqueue(2); sq.debug();   // d: [2]  (3 killed)
    sq.enqueue(1); sq.debug();   // d: [1]  (2 killed)
    
    assert(sq.findmin() == 1);
    
    std::cout << "test_decreasing PASSED" << std::endl << std::endl;
}

void test_increasing() {
    std::cout << "=== TEST INCREASING INPUT ===" << std::endl;
    SuperQueue sq;
    
    sq.enqueue(1); sq.debug();   // d: [1]
    sq.enqueue(2); sq.debug();   // d: [1, 2]
    sq.enqueue(3); sq.debug();   // d: [1, 2, 3]
    sq.enqueue(4); sq.debug();   // d: [1, 2, 3, 4]
    sq.enqueue(5); sq.debug();   // d: [1, 2, 3, 4, 5]
    
    assert(sq.findmin() == 1);
    
    sq.dequeue(); sq.debug();    // d: [2, 3, 4, 5]
    assert(sq.findmin() == 2);
    
    std::cout << "test_increasing PASSED" << std::endl << std::endl;
}

void test_duplicates() {
    std::cout << "=== TEST DUPLICATES ===" << std::endl;
    SuperQueue sq;
    
    sq.enqueue(2); sq.debug();   // d: [2]
    sq.enqueue(2); sq.debug();   // d: [2, 2]  (both kept, 2 < 2 is false)
    sq.enqueue(2); sq.debug();   // d: [2, 2, 2]
    
    assert(sq.findmin() == 2);
    
    sq.dequeue(); sq.debug();    // d: [2, 2]
    assert(sq.findmin() == 2);
    
    sq.dequeue(); sq.debug();    // d: [2]
    assert(sq.findmin() == 2);
    
    sq.dequeue(); sq.debug();    // d: []
    assert(sq.empty());
    
    std::cout << "test_duplicates PASSED" << std::endl << std::endl;
}

void test_mixed() {
    std::cout << "=== TEST MIXED ===" << std::endl;
    SuperQueue sq;
    
    sq.enqueue(10); sq.debug();
    sq.enqueue(5);  sq.debug();
    sq.enqueue(20); sq.debug();
    sq.enqueue(3);  sq.debug();  // d: [3]  (5, 20 killed by 3)
    
    assert(sq.findmin() == 3);
    
    sq.enqueue(15); sq.debug();  // d: [3, 15]
    sq.enqueue(7);  sq.debug();  // d: [3, 7]  (15 killed by 7)
    
    assert(sq.findmin() == 3);
    
    sq.dequeue(); sq.debug();    // remove 10, d unchanged
    sq.dequeue(); sq.debug();    // remove 5, d unchanged
    sq.dequeue(); sq.debug();    // remove 20, d unchanged
    sq.dequeue(); sq.debug();    // remove 3, d: [7]
    
    assert(sq.findmin() == 7);
    
    std::cout << "test_mixed PASSED" << std::endl << std::endl;
}

void test_empty_exception() {
    std::cout << "=== TEST EMPTY EXCEPTION ===" << std::endl;
    SuperQueue sq;
    
    try {
        sq.findmin();
        std::cout << "FAILED: Expected exception" << std::endl;
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    std::cout << "test_empty_exception PASSED" << std::endl << std::endl;
}

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "SUPERQUEUE TEST SUITE" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl << std::endl;
    
    test_basic();
    test_decreasing();
    test_increasing();
    test_duplicates();
    test_mixed();
    test_empty_exception();
    
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "ALL TESTS PASSED!" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    
    return 0;
}

#include <iostream>
#include <stack>
#include <climits>
#include <cassert>
#include <vector>

// SuperStack: O(1) push, O(1) pop, O(1) findMax
// Two-stack approach: main_stack stores values, max_stack stores running max at each depth

class SuperStack {
private:
    std::stack<int> main_stack;
    std::stack<int> max_stack;

public:
    // TODO: Implement push(x) - O(1)
    // main_stack.push(x)
    // max_stack.push(max(x, max_stack.top())) if not empty, else push(x)
    void push(int x) {
        
        main_stack.push(x);
    
        if ( max_stack.empty())
        {
            max_stack.push(x);
        }
        else
        {
            max_stack.push(std::max(x, max_stack.top()));   
        }
    }

    // TODO: Implement pop() - O(1)
    // main_stack.pop() AND max_stack.pop() - BOTH must pop together
    void pop() {
        // YOUR CODE HERE
        main_stack.pop();
        
        max_stack.pop();
    }

    // TODO: Implement findMax() - O(1)
    // return max_stack.top() - query only, no removal
    int findMax() {
        // YOUR CODE HERE
        return max_stack.top();
    }

    // TODO: Implement top() - O(1)
    int top() {
        // YOUR CODE HERE
        return main_stack.top();
    }

    // TODO: Implement empty() - O(1)
    bool empty() {
        // YOUR CODE HERE
        return main_stack.empty();
    }

    // TODO: Implement size() - O(1)
    size_t size() {
        // YOUR CODE HERE
        return max_stack.size();
    }
};

// ============ TEST CASES ============

void test_basic_operations() {
    std::cout << "Test: basic_operations... ";
    SuperStack s;
    
    // push(5), push(3), push(8), push(2)
    // main=[5,3,8,2], max=[5,5,8,8]
    s.push(5);
    assert(s.findMax() == 5); // max after first push
    
    s.push(3);
    assert(s.findMax() == 5); // 3 < 5, max stays 5
    
    s.push(8);
    assert(s.findMax() == 8); // 8 > 5, max becomes 8
    
    s.push(2);
    assert(s.findMax() == 8); // 2 < 8, max stays 8
    
    std::cout << "PASSED\n";
}

void test_pop_restores_max() {
    std::cout << "Test: pop_restores_max... ";
    SuperStack s;
    
    // push(5), push(3), push(8), push(2)
    s.push(5);
    s.push(3);
    s.push(8);
    s.push(2);
    // main=[5,3,8,2], max=[5,5,8,8]
    
    assert(s.findMax() == 8);
    
    s.pop(); // remove 2
    // main=[5,3,8], max=[5,5,8]
    assert(s.findMax() == 8);
    
    s.pop(); // remove 8 - THIS IS THE KEY TEST
    // main=[5,3], max=[5,5]
    assert(s.findMax() == 5); // max must revert to 5
    
    s.pop(); // remove 3
    // main=[5], max=[5]
    assert(s.findMax() == 5);
    
    s.pop(); // remove 5
    // main=[], max=[]
    assert(s.empty());
    
    std::cout << "PASSED\n";
}

void test_ascending_sequence() {
    std::cout << "Test: ascending_sequence... ";
    SuperStack s;
    
    // push(1), push(3), push(6), push(9)
    // main=[1,3,6,9], max=[1,3,6,9]
    s.push(1);
    assert(s.findMax() == 1);
    
    s.push(3);
    assert(s.findMax() == 3);
    
    s.push(6);
    assert(s.findMax() == 6);
    
    s.push(9);
    assert(s.findMax() == 9);
    
    s.pop();
    assert(s.findMax() == 6);
    
    s.pop();
    assert(s.findMax() == 3);
    
    std::cout << "PASSED\n";
}

void test_descending_sequence() {
    std::cout << "Test: descending_sequence... ";
    SuperStack s;
    
    // push(9), push(6), push(3), push(1)
    // main=[9,6,3,1], max=[9,9,9,9]
    s.push(9);
    s.push(6);
    s.push(3);
    s.push(1);
    
    assert(s.findMax() == 9);
    
    s.pop();
    assert(s.findMax() == 9);
    
    s.pop();
    assert(s.findMax() == 9);
    
    s.pop();
    assert(s.findMax() == 9);
    
    std::cout << "PASSED\n";
}

void test_all_same() {
    std::cout << "Test: all_same... ";
    SuperStack s;
    
    // push(7), push(7), push(7)
    // main=[7,7,7], max=[7,7,7]
    s.push(7);
    s.push(7);
    s.push(7);
    
    assert(s.findMax() == 7);
    
    s.pop();
    assert(s.findMax() == 7);
    
    s.pop();
    assert(s.findMax() == 7);
    
    std::cout << "PASSED\n";
}

void test_single_element() {
    std::cout << "Test: single_element... ";
    SuperStack s;
    
    s.push(42);
    assert(s.findMax() == 42);
    assert(s.top() == 42);
    assert(!s.empty());
    assert(s.size() == 1);
    
    s.pop();
    assert(s.empty());
    assert(s.size() == 0);
    
    std::cout << "PASSED\n";
}

void test_negative_numbers() {
    std::cout << "Test: negative_numbers... ";
    SuperStack s;
    
    // push(-5), push(-3), push(-8), push(-2)
    // main=[-5,-3,-8,-2], max=[-5,-3,-3,-2]
    s.push(-5);
    assert(s.findMax() == -5);
    
    s.push(-3);
    assert(s.findMax() == -3); // -3 > -5
    
    s.push(-8);
    assert(s.findMax() == -3); // -8 < -3
    
    s.push(-2);
    assert(s.findMax() == -2); // -2 > -3
    
    s.pop();
    assert(s.findMax() == -3);
    
    std::cout << "PASSED\n";
}

void test_mixed_positive_negative() {
    std::cout << "Test: mixed_positive_negative... ";
    SuperStack s;
    
    // push(-10), push(5), push(-3), push(8), push(-1)
    s.push(-10);
    assert(s.findMax() == -10);
    
    s.push(5);
    assert(s.findMax() == 5);
    
    s.push(-3);
    assert(s.findMax() == 5);
    
    s.push(8);
    assert(s.findMax() == 8);
    
    s.push(-1);
    assert(s.findMax() == 8);
    
    // pop sequence
    s.pop(); // remove -1
    assert(s.findMax() == 8);
    
    s.pop(); // remove 8
    assert(s.findMax() == 5);
    
    s.pop(); // remove -3
    assert(s.findMax() == 5);
    
    s.pop(); // remove 5
    assert(s.findMax() == -10);
    
    std::cout << "PASSED\n";
}

void test_large_sequence() {
    std::cout << "Test: large_sequence... ";
    SuperStack s;
    
    // push [10,4,15,2,15,8,3]
    // main=[10,4,15,2,15,8,3]
    // max =[10,10,15,15,15,15,15]
    std::vector<int> vals = {10, 4, 15, 2, 15, 8, 3};
    std::vector<int> expected_max = {10, 10, 15, 15, 15, 15, 15};
    
    for (size_t i = 0; i < vals.size(); ++i) {
        s.push(vals[i]);
        assert(s.findMax() == expected_max[i]);
    }
    
    // pop and verify max reverts correctly
    // after pop: max should be [10,10,15,15,15,15]
    s.pop(); // remove 3
    assert(s.findMax() == 15);
    
    s.pop(); // remove 8
    assert(s.findMax() == 15);
    
    s.pop(); // remove 15
    assert(s.findMax() == 15);
    
    s.pop(); // remove 2
    assert(s.findMax() == 15);
    
    s.pop(); // remove 15 - KEY: max drops to 10
    assert(s.findMax() == 10);
    
    s.pop(); // remove 4
    assert(s.findMax() == 10);
    
    std::cout << "PASSED\n";
}

void test_duplicate_max() {
    std::cout << "Test: duplicate_max... ";
    SuperStack s;
    
    // push(5), push(10), push(10), push(3)
    // main=[5,10,10,3], max=[5,10,10,10]
    s.push(5);
    s.push(10);
    s.push(10); // duplicate max
    s.push(3);
    
    assert(s.findMax() == 10);
    
    s.pop(); // remove 3
    assert(s.findMax() == 10);
    
    s.pop(); // remove first 10 - max should still be 10
    assert(s.findMax() == 10);
    
    s.pop(); // remove second 10 - max drops to 5
    assert(s.findMax() == 5);
    
    std::cout << "PASSED\n";
}

void test_interleaved_push_pop() {
    std::cout << "Test: interleaved_push_pop... ";
    SuperStack s;
    
    s.push(5);
    assert(s.findMax() == 5);
    
    s.push(10);
    assert(s.findMax() == 10);
    
    s.pop(); // remove 10
    assert(s.findMax() == 5);
    
    s.push(3);
    assert(s.findMax() == 5);
    
    s.push(15);
    assert(s.findMax() == 15);
    
    s.pop(); // remove 15
    assert(s.findMax() == 5);
    
    s.pop(); // remove 3
    assert(s.findMax() == 5);
    
    s.pop(); // remove 5
    assert(s.empty());
    
    std::cout << "PASSED\n";
}

int main() {
    std::cout << "=== SuperStack Tests ===\n\n";
    
    test_basic_operations();
    test_pop_restores_max();
    test_ascending_sequence();
    test_descending_sequence();
    test_all_same();
    test_single_element();
    test_negative_numbers();
    test_mixed_positive_negative();
    test_large_sequence();
    test_duplicate_max();
    test_interleaved_push_pop();
    
    std::cout << "\n=== All Tests Passed ===\n";
    return 0;
}

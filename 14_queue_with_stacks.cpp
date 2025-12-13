#include <iostream>
#include <stack>
#include <cassert>

class QueueWithStacks {
private:
    std::stack<int> s1; // Input stack
    std::stack<int> s2; // Output stack

public:
    // enqueue(x): x=5 → s1.push(5) → S1=[5] S2=[] → x=10 → s1.push(10) → S1=[5,10] S2=[] → S1.size()=2
    void enqueue(int x) {
        s1.push(x);  // O(1) always → S1 grows by 1 → S1.top()=x after call
    }

    // dequeue(): S1=[5,10] S2=[] → s2.empty()=true → transfer loop → S1.top()=10 → s2.push(10) → S1.pop() → S1=[5] S2=[10]
    //            → S1.top()=5 → s2.push(5) → S1.pop() → S1=[] S2=[10,5] → S2.top()=5 → val=5 → s2.pop() → return 5
    // if S2=[10] already → s2.empty()=false → skip transfer → val=S2.top()=10 → return 10 → O(1)
    int dequeue() {
        if (s2.empty()) {                    // S2=[] → true → transfer needed
            while (!s1.empty()) {            // S1=[A,B,C] → loop 3 times
                s2.push(s1.top());           // iter1: s2.push(C) → S2=[C] | iter2: s2.push(B) → S2=[C,B] | iter3: s2.push(A) → S2=[C,B,A]
                s1.pop();                    // iter1: S1=[A,B] | iter2: S1=[A] | iter3: S1=[]
            }                                // after loop: S1=[] S2=[C,B,A] → S2.top()=A=oldest
        }
        int val = s2.top();                  // S2=[C,B,A] → val=A
        s2.pop();                            // S2=[C,B]
        return val;                          // return A → FIFO ✓
    }

    // empty(): S1=[] S2=[10] → s1.empty()=true s2.empty()=false → true && false = false → not empty ✓
    //          S1=[5] S2=[] → s1.empty()=false → false && anything = false → not empty ✓
    //          S1=[] S2=[] → true && true = true → empty ✓
    bool empty() {
        return s1.empty() && s2.empty();     // both must be empty for queue to be empty
    }
};

void test_simple_fifo() {
    QueueWithStacks q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    assert(q.dequeue() == 1);
    assert(q.dequeue() == 2);
    assert(q.dequeue() == 3);
    std::cout << "test_simple_fifo passed" << std::endl;
}

void test_interleaved() {
    QueueWithStacks q;
    q.enqueue(10);
    q.enqueue(20);
    assert(q.dequeue() == 10);
    q.enqueue(30);
    assert(q.dequeue() == 20);
    assert(q.dequeue() == 30);
    std::cout << "test_interleaved passed" << std::endl;
}

void test_empty() {
    QueueWithStacks q;
    assert(q.empty() == true);
    q.enqueue(1);
    assert(q.empty() == false);
    q.dequeue();
    assert(q.empty() == true); // Should be empty after removing the only element
    std::cout << "test_empty passed" << std::endl;
}

int main() {
    test_simple_fifo();
    test_interleaved();
    test_empty();
    return 0;
}

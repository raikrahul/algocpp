#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

// Problem 4: Maximize the tip
// Given an array of tips, return the maximum amount of money the owner can make.
// Cost of serving i-th customer at time t is tips[i] - t. Min tip is 0.
// Prototype:
long long getMaxMoney(int tips[], int n) {
    // Axiomatic Derivation of Sort Order:
    // Case 1: T=[1, 10], N=2. Time slots t=0, 1.
    // OPTION A (Ascending [1, 10]):
    //   t=0: Tip=1. Net=1-0=1. Status: >0 (Paid).
    //   t=1: Tip=10. Net=10-1=9. Status: >0 (Paid).
    //   Total = 1 + 9 = 10.
    // OPTION B (Descending [10, 1]):
    //   t=0: Tip=10. Net=10-0=10. Status: >0 (Paid).
    //   t=1: Tip=1. Net=1-1=0. Status: =0 (Paid 0).
    //   Total = 10 + 0 = 10.
    //   Result: 10 == 10. No difference? WAIT.
    // Case 2: T=[10, 5, 1], N=3. Slots 0, 1, 2.
    // OPTION A (Ascending [1, 5, 10]):
    //   1@0(1) + 5@1(4) + 10@2(8) = 13.
    // OPTION B (Descending [10, 5, 1]):
    //   10@0(10) + 5@1(4) + 1@2(neg->0) = 14.
    //   Surprise: 14 > 13. Why?
    //   In Opt A, 1 at t=0 contributed 1. In Opt B, 1 at t=2 contributed 0. Loss of 1.
    //   In Opt A, 10 at t=2 contributed 8. In Opt B, 10 at t=0 contributed 10. Gain of 2.
    //   Net Change: Gain 2 (from 10) - Loss 1 (from 1) = +1.
    //   The "Value at Risk" for 10 is 1/sec. For 1 it is 1/sec.
    //   BUT 1 hits zero at t=1. 10 fits zero at t=10.
    //   Delaying 10 by 2 sec costs 2. Delaying 1 by 2 sec costs 1 (it floors at 0).
    //   Therefore, delaying the larger number costs MORE absolute value than delaying the small number.
    //   To minimize cost, we must NOT delay the large numbers.
    //   ∴ Sort Descending.
    // 41. Sort tips in descending order to minimize loss from time delay
    // TODO: Write the sort command derived from axioms
    
    // 42. Accumulate tips. Trace: T=[10, 5, 1] (Sorted).
    // i=0: val=10. t=0. 10 > 0? Yes. Add 10-0=10. Total=10.
    // i=1: val=5. t=1. 5 > 1? Yes. Add 5-1=4. Total=10+4=14.
    // i=2: val=1. t=2. 1 > 2? No (1-2 = -1). Add 0. Total=14.
    long long total_money = 0;
    // TODO: Write the accumulation loop derived from axioms
    std::sort(tips, tips + n,  std::greater<int>());
    for (int i = 0; i < n; ++i) {
        {
            auto current_money = tips[i] - i;
            total_money += std::max(0, current_money);
        }   
    }
    
    return total_money;
}

void test_cases() {
    // Test 1: Simple case
    {
        int tips[] = {1, 2, 3};
        long long res = getMaxMoney(tips, 3);
        // Sorted: 3, 2, 1
        // 3-0 + 2-1 + 1-2 = 3 + 1 + 0 = 4
        assert(res == 4);
        std::cout << "Test 1 Passed" << std::endl;
    }
    // Test 2: Zero handling
    {
        int tips[] = {1, 10};
        long long res = getMaxMoney(tips, 2);
        // Sorted: 10, 1
        // 10-0 + 1-1 = 10 + 0 = 10
        assert(res == 10);
        std::cout << "Test 2 Passed" << std::endl;
    }
    // Test 3: All zeros
    {
        int tips[] = {0, 0, 0};
        long long res = getMaxMoney(tips, 3);
        assert(res == 0);
        std::cout << "Test 3 Passed" << std::endl;
    }
    // Test 4: Single element
    {
        int tips[] = {5};
        long long res = getMaxMoney(tips, 1);
        assert(res == 5);
        std::cout << "Test 4 Passed" << std::endl;
    }
    // Test 5: Decay to zero
    {
        int tips[] = {1, 1, 1};
        long long res = getMaxMoney(tips, 3);
        // Sorted: 1, 1, 1
        // 1-0 + 1-1 + 1-2 = 1 + 0 + 0 = 1
        assert(res == 1);
        std::cout << "Test 5 Passed" << std::endl;
    }
    std::cout << "All Tests Passed" << std::endl;
}

int main() {
    test_cases();
    return 0;
}

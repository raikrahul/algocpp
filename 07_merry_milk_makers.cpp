#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>

/*
 * MERRY MILK MAKERS
 * 
 * Goal: Minimize cost to buy 'totalneed' milk.
 * Inputs:
 *   - totalneed: Amount of milk required.
 *   - nfarmers: Number of farmers.
 *   - a[]: Array of milk amounts available from each farmer.
 *   - p[]: Array of price per unit from each farmer.
 * 
 * Strategy (Derived):
 *   1. We want to pay the LEAST per gallon.
 *   2. Therefore, we should always exhaust the farmer with the lowest price derived from p[i] 
 *      before moving to the next lowest price.
 *   3. This implies sorting the farmers based on price p[i].
 *   4. Iterate through sorted farmers, taking min(need, available) and accumulating cost.
 */

// Function Prototype
struct Farmer {
    int amount;
    int price;
};

bool compareFarmers(const Farmer& a, const Farmer& b) {
    return a.price < b.price;
}

int FindMinCost(int totalneed, int nfarmers, int *a, int *p) {
    // 1. Create vector of Farmers
    std::vector<Farmer> farmers;
    farmers.reserve(nfarmers);
    for (int i = 0; i < nfarmers; ++i) {
        farmers.push_back({a[i], p[i]});
    }

    // 2. Sort by price (cheapest first)
    std::sort(farmers.begin(), farmers.end(), compareFarmers);

    int current_cost = 0;
    int remaining_need = totalneed;

    // 3. Greedy selection
    for (const auto& farmer : farmers) {
        if (remaining_need <= 0) break;

        int amount_to_buy = std::min(remaining_need, farmer.amount);
        current_cost += amount_to_buy * farmer.price;
        remaining_need -= amount_to_buy;
    }

    return current_cost;
}

void runTests() {
    std::cout << "Running tests for Merry Milk Makers...\n";

    // Test 1: Example from problem statement
    // TotalNeed=100, N=5
    // A: 20 40 10 80 30
    // P: 5  9  3  8  6
    // Sorted by Price:
    // (10, 3), (20, 5), (30, 6), (80, 8), (40, 9)
    // Buy:
    // 10 @ 3 = 30  (Need 90)
    // 20 @ 5 = 100 (Need 70)
    // 30 @ 6 = 180 (Need 40)
    // 40 @ 8 = 320 (Need 0)
    // Total: 30+100+180+320 = 630
    {
        int totalneed = 100;
        int nfarmers = 5;
        int a[] = {20, 40, 10, 80, 30};
        int p[] = {5, 9, 3, 8, 6};
        int result = FindMinCost(totalneed, nfarmers, a, p);
        std::cout << "Test 1: result=" << result << " expected=630" << std::endl;
        assert(result == 630);
    }

    // Test 2: Zero need
    // Should cost 0
    {
        int totalneed = 0;
        int nfarmers = 3;
        int a[] = {10, 20, 30};
        int p[] = {1, 2, 3};
        int result = FindMinCost(totalneed, nfarmers, a, p);
        std::cout << "Test 2: result=" << result << " expected=0" << std::endl;
        assert(result == 0);
    }

    // Test 3: Need satisfied by single cheapest farmer
    // Need 5. Cheapest has 10 @ price 2.
    // Cost = 5 * 2 = 10.
    {
        int totalneed = 5;
        int nfarmers = 2;
        int a[] = {10, 100};
        int p[] = {2, 5};
        int result = FindMinCost(totalneed, nfarmers, a, p);
        std::cout << "Test 3: result=" << result << " expected=10" << std::endl;
        assert(result == 10);
    }
    
    // Test 4: Need requires partial from last farmer
    // Need: 15
    // F1: 10 @ 2 (Cost 20, Need 5)
    // F2: 10 @ 4 (Take 5 @ 4 = 20, Need 0)
    // Total: 40
    {
        int totalneed = 15;
        int nfarmers = 2;
        int a[] = {10, 10};
        int p[] = {2, 4};
        int result = FindMinCost(totalneed, nfarmers, a, p);
        std::cout << "Test 4: result=" << result << " expected=40" << std::endl;
        assert(result == 40);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    runTests();
    return 0;
}

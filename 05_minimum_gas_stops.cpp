#include <iostream>
#include <vector>
#include <cassert>
#include <string>

// Problem: Gas stations s1,s2,...,sn along highway Pune→Mumbai
// Tank capacity = M miles (full tank)
// d[i] = distance from station s[i-1] to s[i], each d[i] ≤ M
// Start at s1 (Pune) with full tank
// Find minimum gas stops to reach sn (Mumbai)
//
// Example 1: d[]={5,3,4,2}, n=5, M=7
// s1→s2: tank=7→7-5=2, 2<3→refuel→tank=7, stops=1
// s2→s3: tank=7-3=4, 4≥4→no refuel
// s3→s4: tank=4-4=0, 0<2→refuel→tank=7, stops=2
// s4→s5: tank=7-2=5→ARRIVED
// Answer: 2 stops
//
// Example 2: d[]={7,7,7}, n=4, M=7
// tank=7→0 (stop=1) →7→0 (stop=2) →7→0→ARRIVED
// Answer: 2 stops
//
// Example 3: d[]={1,1,1,1,1,1,1}, n=8, M=7
// tank=7→6→5→4→3→2→1→0→ARRIVED
// Answer: 0 stops (tank covers all 7 legs)

// Function signature as given
// d[] = array of n-1 distances (0-indexed: d[i] = distance station_i to station_{i+1})
// n = number of stations
// m = tank capacity in miles
int FindMinStops(int d[], int n, int m) {
    // YOUR IMPLEMENTATION HERE
    // DO NOT WRITE SOLUTION - DERIVE BY HAND FIRST
    //
    // TRACE: m=7, d[]={5,3,4,2}, n=5
    // i=0: tank=7, d[0]=5 → 7<5? NO → tank=7-5=2
    // i=1: tank=2, d[1]=3 → 2<3? YES → tank=7, stops=1 → tank=7-3=4
    // i=2: tank=4, d[2]=4 → 4<4? NO → tank=4-4=0
    // i=3: tank=0, d[3]=2 → 0<2? YES → tank=7, stops=2 → tank=7-2=5
    // return 2
    return -1; // STUB
}

// Helper to run test with vector
int FindMinStopsVec(const std::vector<int>& distances, int n, int m) {
    std::vector<int> d = distances;
    return FindMinStops(d.data(), n, m);
}

void test_basic_case() {
    // d[]={5,3,4,2}, n=5, M=7
    // Trace: tank starts 7
    // leg0: 7-5=2, 2<3→refuel→7, stops=1, 7-3=4
    // leg1: 4≥4→4-4=0, 0<2→refuel→7, stops=2, 7-2=5
    // Expected: 2
    std::vector<int> d = {5, 3, 4, 2};
    int result = FindMinStopsVec(d, 5, 7);
    assert(result == 2);
    std::cout << "test_basic_case PASSED: expected=2, got=" << result << "\n";
}

void test_all_equal_small() {
    // d[]={2,2,2,2}, n=5, M=7
    // tank=7→5→3→1→refuel(stops=1)→7→5→ARRIVED
    // Wait: only 4 distances for 5 stations
    // leg0: 7-2=5, 5≥2→no
    // leg1: 5-2=3, 3≥2→no
    // leg2: 3-2=1, 1<2→refuel→7, stops=1, 7-2=5
    // leg3: 5-2=3→ARRIVED
    // Expected: 1
    std::vector<int> d = {2, 2, 2, 2};
    int result = FindMinStopsVec(d, 5, 7);
    assert(result == 1);
    std::cout << "test_all_equal_small PASSED: expected=1, got=" << result << "\n";
}

void test_all_max() {
    // d[]={7,7,7}, n=4, M=7
    // leg0: 7-7=0, 0<7→refuel→7, stops=1, 7-7=0
    // leg1: 0<7→refuel→7, stops=2, 7-7=0
    // leg2: 0<7→refuel→7, stops=3, 7-7=0→ARRIVED
    // WAIT: 3 distances, 4 stations, 3 legs
    // After leg2 we arrive, so no refuel needed after arrival
    // leg0: tank=7, 7<7? NO→7-7=0
    // leg1: tank=0, 0<7? YES→tank=7, stops=1→7-7=0
    // leg2: tank=0, 0<7? YES→tank=7, stops=2→7-7=0→ARRIVED
    // Expected: 2
    std::vector<int> d = {7, 7, 7};
    int result = FindMinStopsVec(d, 4, 7);
    assert(result == 2);
    std::cout << "test_all_max PASSED: expected=2, got=" << result << "\n";
}

void test_no_stops_needed() {
    // d[]={1,1,1,1,1,1,1}, n=8, M=7
    // 7 legs, each 1 mile, total 7 miles
    // tank=7→6→5→4→3→2→1→0→ARRIVED
    // No refuel needed ever
    // Expected: 0
    std::vector<int> d = {1, 1, 1, 1, 1, 1, 1};
    int result = FindMinStopsVec(d, 8, 7);
    assert(result == 0);
    std::cout << "test_no_stops_needed PASSED: expected=0, got=" << result << "\n";
}

void test_single_leg() {
    // d[]={6}, n=2, M=7
    // Only one leg
    // tank=7, 7<6? NO→7-6=1→ARRIVED
    // Expected: 0
    std::vector<int> d = {6};
    int result = FindMinStopsVec(d, 2, 7);
    assert(result == 0);
    std::cout << "test_single_leg PASSED: expected=0, got=" << result << "\n";
}

void test_single_leg_exact() {
    // d[]={7}, n=2, M=7
    // tank=7, 7<7? NO→7-7=0→ARRIVED
    // Expected: 0
    std::vector<int> d = {7};
    int result = FindMinStopsVec(d, 2, 7);
    assert(result == 0);
    std::cout << "test_single_leg_exact PASSED: expected=0, got=" << result << "\n";
}

void test_every_station_refuel() {
    // d[]={6,6,6}, n=4, M=7
    // leg0: 7-6=1, 1<6→refuel→7, stops=1, 7-6=1
    // leg1: 1<6→refuel→7, stops=2, 7-6=1
    // leg2: 1<6→refuel→7, stops=3, 7-6=1→ARRIVED
    // WAIT: after leg2 we arrive, so we check before driving
    // leg0: tank=7, 7<6? NO→7-6=1
    // leg1: tank=1, 1<6? YES→tank=7, stops=1→7-6=1
    // leg2: tank=1, 1<6? YES→tank=7, stops=2→7-6=1→ARRIVED
    // Expected: 2
    std::vector<int> d = {6, 6, 6};
    int result = FindMinStopsVec(d, 4, 7);
    assert(result == 2);
    std::cout << "test_every_station_refuel PASSED: expected=2, got=" << result << "\n";
}

void test_larger_tank() {
    // d[]={3,5,6,2,8,1}, n=7, M=10
    // leg0: 10-3=7, 7≥5→no
    // leg1: 7-5=2, 2<6→refuel→10, stops=1, 10-6=4
    // leg2: 4≥2→4-2=2, 2<8→refuel→10, stops=2, 10-8=2
    // leg3: 2≥1→2-1=1→ARRIVED
    // WAIT: 6 distances, 7 stations
    // leg0: d[0]=3, tank=10-3=7
    // leg1: d[1]=5, tank=7-5=2
    // leg2: d[2]=6, 2<6→refuel→10, stops=1, tank=10-6=4
    // leg3: d[3]=2, tank=4-2=2
    // leg4: d[4]=8, 2<8→refuel→10, stops=2, tank=10-8=2
    // leg5: d[5]=1, tank=2-1=1→ARRIVED
    // Expected: 2
    std::vector<int> d = {3, 5, 6, 2, 8, 1};
    int result = FindMinStopsVec(d, 7, 10);
    assert(result == 2);
    std::cout << "test_larger_tank PASSED: expected=2, got=" << result << "\n";
}

void test_uniform_almost_full() {
    // d[]={4,4,4,4}, n=5, M=5
    // leg0: 5-4=1, 1<4→refuel→5, stops=1, 5-4=1
    // leg1: 1<4→refuel→5, stops=2, 5-4=1
    // leg2: 1<4→refuel→5, stops=3, 5-4=1
    // leg3: 1<4→refuel→5, stops=4, 5-4=1→ARRIVED
    // WAIT: we arrive after leg3, so we check BEFORE driving leg3
    // leg0: tank=5, 5<4? NO→5-4=1
    // leg1: tank=1, 1<4? YES→5, stops=1→5-4=1
    // leg2: tank=1, 1<4? YES→5, stops=2→5-4=1
    // leg3: tank=1, 1<4? YES→5, stops=3→5-4=1→ARRIVED
    // Expected: 3
    std::vector<int> d = {4, 4, 4, 4};
    int result = FindMinStopsVec(d, 5, 5);
    assert(result == 3);
    std::cout << "test_uniform_almost_full PASSED: expected=3, got=" << result << "\n";
}

void test_edge_n1() {
    // n=1: only one station, already at destination
    // No distances, no legs
    // Expected: 0
    std::vector<int> d = {};
    int result = FindMinStopsVec(d, 1, 7);
    assert(result == 0);
    std::cout << "test_edge_n1 PASSED: expected=0, got=" << result << "\n";
}

void test_zigzag() {
    // d[]={1,6,1,6,1}, n=6, M=7
    // leg0: 7-1=6, 6≥6→no
    // leg1: 6-6=0, 0<1→refuel→7, stops=1, 7-1=6
    // leg2: 6≥6→6-6=0, 0<1→refuel→7, stops=2, 7-1=6
    // leg3: 6≥6→6-6=0, 0<1→refuel→7, stops=3, 7-1=6→ARRIVED
    // WAIT: 5 distances, 6 stations
    // leg0: d[0]=1, tank=7-1=6
    // leg1: d[1]=6, tank=6, 6<6? NO→6-6=0
    // leg2: d[2]=1, tank=0, 0<1? YES→7, stops=1, 7-1=6
    // leg3: d[3]=6, tank=6, 6<6? NO→6-6=0
    // leg4: d[4]=1, tank=0, 0<1? YES→7, stops=2, 7-1=6→ARRIVED
    // Expected: 2
    std::vector<int> d = {1, 6, 1, 6, 1};
    int result = FindMinStopsVec(d, 6, 7);
    assert(result == 2);
    std::cout << "test_zigzag PASSED: expected=2, got=" << result << "\n";
}

void test_almost_no_stops() {
    // d[]={3,3,3,3,3,3}, n=7, M=10
    // 6 legs × 3 miles = 18 miles, tank=10
    // leg0: 10-3=7
    // leg1: 7-3=4
    // leg2: 4-3=1, 1<3→refuel→10, stops=1, 10-3=7
    // leg3: 7-3=4
    // leg4: 4-3=1, 1<3→refuel→10, stops=2, 10-3=7
    // leg5: 7-3=4→ARRIVED
    // Expected: 2
    std::vector<int> d = {3, 3, 3, 3, 3, 3};
    int result = FindMinStopsVec(d, 7, 10);
    assert(result == 2);
    std::cout << "test_almost_no_stops PASSED: expected=2, got=" << result << "\n";
}

int main() {
    std::cout << "=== Minimum Gas Stops Tests ===\n\n";
    
    test_basic_case();
    test_all_equal_small();
    test_all_max();
    test_no_stops_needed();
    test_single_leg();
    test_single_leg_exact();
    test_every_station_refuel();
    test_larger_tank();
    test_uniform_almost_full();
    test_edge_n1();
    test_zigzag();
    test_almost_no_stops();
    
    std::cout << "\n=== ALL TESTS PASSED ===\n";
    return 0;
}

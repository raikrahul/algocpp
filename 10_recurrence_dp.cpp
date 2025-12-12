#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// Recurrence:
// M(i,j) = 1                              if i = j
// M(i,j) = 2                              if j = i + 1
// M(i,j) = M(i+1,j-1) * M(i+1,j) * M(i,j-1)  if j > i + 1
//
// Compute M(1,n) using bottom-up DP
//
// Time: O(n²) - fill n(n+1)/2 cells, each O(1)
// Space: O(n²) - table M[n+1][n+1]

long long computeM(int n) {
    // n: range [1, n], compute M(1, n)
    // n=1 → M(1,1)=1
    // n=2 → M(1,2)=2
    // n=3 → M(1,3)=M(2,2)*M(2,3)*M(1,2)=1*2*2=4
    // n=4 → M(1,4)=M(2,3)*M(2,4)*M(1,3)=2*4*4=32
    // n=5 → M(1,5)=M(2,4)*M(2,5)*M(1,4)=4*32*32=4096
    // n=6 → M(1,6)=32*4096*4096=536870912
    // n=7 → overflow 64-bit
    
    // TODO: implement bottom-up DP here
    // Step 1: create table M[n+1][n+1]
    // Step 2: fill base case L=1: M[i][i]=1 for i=1..n
    // Step 3: fill base case L=2: M[i][i+1]=2 for i=1..n-1
    // Step 4: fill L=3 to n: M[i][j]=M[i+1][j-1]*M[i+1][j]*M[i][j-1]
    // Step 5: return M[1][n]

    std::vector<std::vector<long long >> M (n+1, std::vector<long long>(n+1, 0));

    for ( int i = 1; i <= n; i++)
    {
        M[i][i] = 1;
    }

    for ( int i = 1; i <= n-1; i++)
    {
        M[i][i+1] = 2;
    }

    for ( int L = 3; L<=n; L++)
    {
        for ( int i = 1; i <= n-L+1; i++)
        {
           int j = i + L - 1;
           M[i][j] = M[i+1][j-1]*M[i+1][j]*M[i][j-1];
        }
    }

    return M[1][n];
}

void test_n1() {
    // n=1 → M(1,1) = 1 (base case i=j)
    assert(computeM(1) == 1);
    cout << "n=1: M(1,1)=1 ✓" << endl;
}

void test_n2() {
    // n=2 → M(1,2) = 2 (base case j=i+1)
    assert(computeM(2) == 2);
    cout << "n=2: M(1,2)=2 ✓" << endl;
}

void test_n3() {
    // n=3 → M(1,3) = M(2,2) * M(2,3) * M(1,2) = 1 * 2 * 2 = 4
    // M(2,2)=1 (i=j), M(2,3)=2 (j=i+1), M(1,2)=2 (j=i+1)
    assert(computeM(3) == 4);
    cout << "n=3: M(1,3)=1*2*2=4 ✓" << endl;
}

void test_n4() {
    // n=4 → M(1,4) = M(2,3) * M(2,4) * M(1,3) = 2 * 4 * 4 = 32
    // M(2,3)=2 (j=i+1), M(2,4)=M(3,3)*M(3,4)*M(2,3)=1*2*2=4, M(1,3)=4 (from test_n3)
    assert(computeM(4) == 32);
    cout << "n=4: M(1,4)=2*4*4=32 ✓" << endl;
}

void test_n5() {
    // n=5 → M(1,5) = M(2,4) * M(2,5) * M(1,4) = 4 * 32 * 32 = 4096
    // M(2,4)=4, M(2,5)=M(3,4)*M(3,5)*M(2,4)=2*4*4=32, M(1,4)=32
    assert(computeM(5) == 4096);
    cout << "n=5: M(1,5)=4*32*32=4096 ✓" << endl;
}

void test_n6() {
    // n=6 → M(1,6) = M(2,5) * M(2,6) * M(1,5) = 32 * 4096 * 4096 = 536870912
    // M(2,5)=32, M(2,6)=M(3,5)*M(3,6)*M(2,5)=4*32*32=4096, M(1,5)=4096
    // 32 * 4096 = 131072, 131072 * 4096 = 536870912 = 2^29
    assert(computeM(6) == 536870912LL);
    cout << "n=6: M(1,6)=32*4096*4096=536870912 ✓" << endl;
}

int main() {
    cout << "Testing M(i,j) recurrence" << endl;
    cout << "M(i,j)=1 if i=j, M(i,j)=2 if j=i+1" << endl;
    cout << "M(i,j)=M(i+1,j-1)*M(i+1,j)*M(i,j-1) if j>i+1" << endl;
    cout << "----------------------------------------" << endl;
    
    test_n1();
    test_n2();
    test_n3();
    test_n4();
    test_n5();
    test_n6();
    
    cout << "----------------------------------------" << endl;
    cout << "All tests passed ✓" << endl;
    cout << "Time: O(n²), Space: O(n²)" << endl;
    
    return 0;
}

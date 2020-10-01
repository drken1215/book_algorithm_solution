#include <iostream>
using namespace std;

// x が条件を満たすかどうか
bool P(int x) {

}

// P(x) = true となる最小の整数 x を返す
int binary_search() {
    // P(left) = False, P(right) = True となるように
    int left, right; 
    
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (P(mid)) right = mid;
        else left = mid;
    }
    return right;
}

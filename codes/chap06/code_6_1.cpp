#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const vector<int> a = {3, 5, 8, 10, 14, 17, 21, 39};

// 目的の値 key の添字を返す (存在しない場合は -1)
int binary_search(int key) {
    int left = 0, right = (int)a.size() - 1; // 配列 a の左端と右端
    while (right >= left) {
        int mid = left + (right - left) / 2; // 区間の真ん中
        if (a[mid] == key) return mid;
        else if (a[mid] > key) right = mid - 1;
        else if (a[mid] < key) left = mid + 1;
    }
    return -1;
}

int main() {
    cout << binary_search(10) << endl; // 3
    cout << binary_search(3) << endl; // 0
    cout << binary_search(39) << endl; // 7

    cout << binary_search(-100) << endl; // -1
    cout << binary_search(9) << endl; // -1
    cout << binary_search(100) << endl; // -1
}

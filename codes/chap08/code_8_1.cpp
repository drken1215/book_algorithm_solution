#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {4, 3, 12, 7, 11, 1, 9, 8, 14, 6};

    // 0 番目の要素を出力 (4)
    cout << a[0] << endl;

    // 2 番目の要素を出力 (12)
    cout << a[2] << endl;

    // 2 番目の要素を 5 に書き換える
    a[2] = 5;

    // 2 番目の要素を出力 (5)
    cout << a[2] << endl;
}

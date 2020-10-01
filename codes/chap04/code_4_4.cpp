#include <iostream>
using namespace std;

int GCD(int m, int n) {
    // ベースケース
    if (n == 0) return m;

    // 再帰呼び出し
    return GCD(n, m % n);
}

int main() {
    cout << GCD(51, 15) << endl; // 3 が出力される
    cout << GCD(15, 51) << endl; // 3 が出力される
}

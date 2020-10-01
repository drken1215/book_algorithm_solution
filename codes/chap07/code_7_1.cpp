#include <iostream>
#include <vector>
using namespace std;

// コインの金額
const vector<int> value = {500, 100, 50, 10, 5, 1};

int main() {
    // 入力
    int X;
    vector<int> a(6);
    cin >> X;
    for (int i = 0; i < 6; ++i) cin >> a[i];

    // 貪欲法
    int result = 0;
    for (int i = 0; i < 6; ++i) {
        // 枚数制限がない場合の枚数
        int add = X / value[i];

        // 枚数制限を考慮
        if (add > a[i]) add = a[i];

        // 残り金額を求めて，答えに枚数を加算する
        X -= value[i] * add;
        result += add;
    }
    cout << result << endl;
}

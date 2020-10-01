#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 入力を受け取る
    int N, v;
    cin >> N >> v;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    
    // 線形探索
    bool exist = false;   // 初期値は false に
    for (int i = 0; i < N; ++i) {
        if (a[i] == v) {
            exist = true;  // 見つかったらフラグを立てる
        }
    }
    
    // 結果出力
    if (exist) cout << "Yes" << endl;
    else cout << "No" << endl;
}

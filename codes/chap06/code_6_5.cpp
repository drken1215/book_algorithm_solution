#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    // 入力
    int N;
    cin >> N;
    vector<long long> H(N), S(N);
    for (int i = 0; i < N; i++) cin >> H[i] >> S[i];

    // 二分探索の上限値を求める
    long long M = 0;
    for (int i = 0; i < N; ++i) M = max(M, H[i] + S[i] * N);

    // 二分探索
    long long left = 0, right = M;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        
        // 判定する
        bool ok = true;
        vector<long long> t(N, 0);  // 各風船を割るまでの制限時間
        for (int i = 0; i < N; ++i) {
            // そもそも mid が初期高度より低かったら false
            if (mid < H[i]) ok = false; 
            else t[i] = (mid - H[i]) / S[i];
        }
        // 時間制限がさし迫っている順にソート する
        sort(t.begin(), t.end()); 
        for (int i = 0; i < N; ++i) {
            // 時間切れ発生の場合は false
            if (t[i] < i) ok = false; 
        }

        if (ok) right = mid;
        else left = mid;
    }

    cout << right << endl;
}

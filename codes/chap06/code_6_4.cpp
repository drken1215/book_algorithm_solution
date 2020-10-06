#include <iostream>
#include <vector>
#include <algorithm> // sort() や lower_bound() に必要です
using namespace std;
const int INF = 20000000; // 十分大きな値に

int main() {
    // 入力を受け取る
    int N, K;
    cin >> N >> K;
    vector<int> a(N), b(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    for (int i = 0; i < N; ++i) cin >> b[i];

    // 暫定最小値を格納する変数
    int min_value = INF;

    // b をソート
    sort(b.begin(), b.end());

    // b に無限大を表す値 (INF) を追加しておく
    // これを行うことで、iter = b.end() となる可能性を除外する
    b.push_back(INF);

    // a を固定して解く
    for (int i = 0; i < N; ++i) {
        // b の中で K - a[i] 以上の範囲での最小値を示すイテレータ
        auto iter = lower_bound(b.begin(), b.end(), K - a[i]);

        // イテレータの示す値を取り出す
        int val = *iter;

        // min_value と比較する
        if (a[i] + val < min_value) {
            min_value = a[i] + val;
        }
    }
    cout << min_value << endl;
}

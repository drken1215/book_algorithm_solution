#include <iostream>
#include <vector>
using namespace std;

template<class T> void chmin(T& a, T b) {
    if (a > b) {
        a = b;
    }
}

const long long INF = 1LL << 60; // 十分大きい値とする (ここでは 2^60)

// 入力データと，メモ用の DP テーブル
int N;
vector<long long> h;
vector<long long> dp;

long long rec(int i) {
    // DP の値が更新されていたらそのままリターン
    if (dp[i] < INF) return dp[i];

    // ベースケース: 足場 0 のコストは 0
    if (i == 0) return 0;

    // 答えを表す変数を INF で初期化する
    long long res = INF;

    // 足場 i - 1 から来た場合
    chmin(res, rec(i - 1) + abs(h[i] - h[i - 1])); 
    
    // 足場 i - 2 から来た場合
    if (i > 1) {
        chmin(res, rec(i - 2) + abs(h[i] - h[i - 2]));
    }

    // 結果をメモしながら、返す
    return dp[i] = res;
}

int main() {
    // 入力受け取り
    cin >> N;
    h.resize(N);
    for (int i = 0; i < N; ++i) cin >> h[i];

    // 初期化 (最小化問題なので INF に初期化)
    dp.assign(N, INF);

    // 答え
    cout << rec(N - 1) << endl;
}

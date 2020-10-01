#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using Graph = vector<vector<int>>;

// 入力
int N; // 頂点数
vector<long long> w; // 各頂点の重み
Graph G; // グラフ

// 木上の動的計画法テーブル
vector<int> dp1, dp2;

void dfs(int v, int p = -1) {
    // 最初に各子頂点を探索しておきます
    for (auto ch : G[v]) {
        if (ch == p) continue;
        dfs(ch, v);
    }

    // 帰りがけ時に動的計画法
    dp1[v] = 0, dp2[v] = w[v]; // 初期条件
    for (auto ch : G[v]) {
        if (ch == p) continue;
        dp1[v] += max(dp1[ch], dp2[ch]);
        dp2[v] += dp1[ch];
    }
}

int main() {
    // 頂点数 (木なので辺数は N - 1 で確定)
    cin >> N;

    // 重みとグラフの入力受取
    w.resize(N);
    for (int i = 0; i < N; ++i) cin >> w[i];
    G.clear(); G.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 探索
    int root = 0; // 仮に頂点 0 を根とする
    dp1.assign(N, 0), dp2.assign(N, 0);
    dfs(root);

    // 結果
    cout << max(dp1[root], dp2[root]) << endl;
}

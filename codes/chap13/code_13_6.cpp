#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;

// トポロジカルソートする
vector<bool> seen;
vector<int> order; // トポロジカルソート順を表す
void rec(const Graph &G, int v) {
    seen[v] = true;
    for (auto next_v : G[v]) {
        if (seen[next_v]) continue; // すでに訪問済みなら探索しない
        rec(G, next_v);
    }

    // v-out を記録する
    order.push_back(v);
}

int main() {
    int N, M;
    cin >> N >> M; // 頂点数と枝数
    Graph G(N); // 頂点数 N のグラフ
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    // 探索
    seen.assign(N, false); // 初期状態では全頂点が未訪問
    order.clear(); // トポロジカルソート順
    for (int v = 0; v < N; ++v) {
        if (seen[v]) continue; // すでに訪問済みなら探索しない
        rec(G, v);
    }
    reverse(order.begin(), order.end()); // 逆順に

    // 出力
    for (auto v : order) cout << v << " -> ";
    cout << endl;
}

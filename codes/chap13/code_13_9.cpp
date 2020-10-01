#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

// 木上の探索
vector<int> depth;
vector<int> subtree_size;
void dfs(const Graph &G, int v, int p = -1, int d = 0) {
    depth[v] = d;
    for (auto c : G[v]) {
        if (c == p) continue; // 探索が親方向へ逆流するのを防ぐ
        dfs(G, c, v, d + 1);
    }

    // 帰りがけ時に、部分木サイズを求める
    subtree_size[v] = 1; // 自分自身
    for (auto c : G[v]) {
        if (c == p) continue;

        // 子頂点を根とする部分きのサイズを加算する
        subtree_size[v] += subtree_size[c]; 
    }
}

int main() {
    // 頂点数 (木なので辺数は N - 1 で確定)
    int N; 
    cin >> N;

    // グラフ入力受取
    Graph G(N);
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 探索
    int root = 0; // 仮に頂点 0 を根とする
    depth.assign(N, 0);
    subtree_size.assign(N, 0);
    dfs(G, root);

    // 結果
    for (int v = 0; v < N; ++v) {
        cout << v << ": depth = " << depth[v]
        << ", subtree_size = " << subtree_size[v] << endl;
    }
}

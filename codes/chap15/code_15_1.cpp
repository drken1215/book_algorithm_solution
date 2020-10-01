#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find
struct UnionFind {
    vector<int> par, siz;

    // 初期化
    UnionFind(int n) : par(n, -1) , siz(n, 1) { }
    
    // 根を求める
    int root(int x) {
        if (par[x] == -1) return x; // x が根の場合は x を返す
        else return par[x] = root(par[x]);
    }

    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    // x を含むグループと y を含むグループとを併合する
    bool unite(int x, int y) {
        // x, y をそれぞれ根まで移動する
        x = root(x);
        y = root(y);

        // すでに同じグループのときは何もしない
        if (x == y) return false; 

        // union by size (y 側のサイズが小さくなるようにする)
        if (siz[x] < siz[y]) swap(x, y);

        // y を x の子とする
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    // x を含むグループのサイズ
    int size(int x) {
        return siz[root(x)];
    }
};

// 辺 e = (u, v) を {w(e), {u, v}} で表す
using Edge = pair<int, pair<int,int>>;

int main() {
    // 入力
    int N, M; // 頂点数と辺数
    cin >> N >> M;
    vector<Edge> edges(M); // 辺集合
    for (int i = 0; i < M; ++i) {
        int u, v, w; // w は重み
        cin >> u >> v >> w;
        edges[i] = Edge(w, make_pair(u, v));
    }

    // 各辺を，辺の重みが小さい順にソートする
    // pair はデフォルトで (第一要素, 第二要素) の辞書順比較
    sort(edges.begin(), edges.end());

    // クラスカル法
    long long res = 0;
    UnionFind uf(N);
    for (int i = 0; i < M; ++i) {
        int w = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        // 辺 (u, v) の追加によってサイクルが形成されるときは追加しない
        if (uf.issame(u, v)) continue;

        // 辺 (u, v) を追加する
        res += w;
        uf.unite(u, v);
    }
    cout << res << endl;
}

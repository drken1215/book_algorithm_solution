#include <iostream>
#include <vector>
using namespace std;

// ここでは重みを表す型を long long 型とする
struct Edge {
    int to; // 隣接頂点番号
    long long w; // 重み
    Edge(int to, long long w) : to(to), w(w) {}
};
    
// 各頂点の隣接リストを，辺集合で表す
using Graph = vector<vector<Edge>>;

int main() {
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        G[a].push_back(Edge(b, w));
    }
}

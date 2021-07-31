# 15.1 (基本カットセットの性質)

無向グラフ G の最小全域木 T と、それに含まれる辺 e に対して、T, e に関する基本カットセットを C とします。C に含まれる e 以外の任意の辺を f とします。このとき、T' = T - e + f も全域木となります。T が最小全域木であることから、

　　　w(T) <= w(T') = w(T) - w(e) + w(f)

となります。これより、w(e) <= w(f) であることが導かれました。

　

# 15.2 (メディアンが最小の全域木)

連結な無向グラフ G (頂点数 N、辺数 M) の最小全域木を T、他の任意の全域木を S とします。T に含まれる辺の重みを小さい順に t[1], t[2], ..., t[N-1] とし、S に含まれる辺の重みを小さい順に s[1], s[2], ..., s[N-1] とします。

このとき、

- t[1] <= s[1]
- t[2] <= s[2]
- ...
- t[N-1] <= s[N-1]

が成り立つことが知られています。つまり最小全域木は、(t の総和) <= (s の総和) を満たすだけでなく、「その全域木に含まれる各辺の重みのうち k 番目に小さな値」についても最小な全域木となっているのです。

このことから、最小全域木 (一般に複数考えられます) に含まれる辺の重みを小さい順にソートして得られる数列が、常に一定であることも従います。

以上の性質の証明については、[問題の公式解説](https://jag-icpc.org/?plugin=attach&refer=2012%2FPractice%2F%E6%A8%A1%E6%93%AC%E5%9C%B0%E5%8C%BA%E4%BA%88%E9%81%B8%2F%E8%AC%9B%E8%A9%95&openfile=MedianTree.pdf)に丁寧に記載されていますので、参考にしていただけたらと思います。

また、問題を解くための具体的なアルゴリズムとしては、通常の最小全域木を求める Kruskal 法を適用すればよいでしょう。計算量は O(N log M) となります。

　

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find
struct UnionFind {
    vector<int> par;

    UnionFind() { }
    UnionFind(int n) : par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) {
        return -par[root(x)];
    }
};

int main() {
    // 辺数
    int N, M;
    while (cin >> N >> M, N) {
        // 辺を表す構造体
        using pint = pair<int, int>;  // 両端点
        using Edge = pair<long long, pint>;  // (重み, 両端点)
        
        // 入力
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].second.first >> edges[i].second.second
                >> edges[i].first;
            --edges[i].second.first;
            --edges[i].second.second;
        }

        // 辺を重み順にソート
        sort(edges.begin(), edges.end());

        // Kruskal 法 
        UnionFind uf(N);
        int num = 0;  // 辺の本数
        long long res = 0;  // 答え
        for (auto e: edges) {
            long long w = e.first;
            int u = e.second.first, v = e.second.second;

            // 辺 (u, v) は追加できない場合
            if (uf.issame(u, v)) continue;

            // 辺 (u, v) を追加するとき
            uf.merge(u, v);
            ++num;

            // メディアンに到達
            if (num == (N + 1) / 2) {
                res = w;
                break;
            }
        }
        cout << res << endl;
    }
}
```

　

# 15.3 (最小全域木に必ず含まれる辺)

まずは愚直な解法を考えてみましょう。グラフ G の各辺 e に対して、

+ 元のグラフ G の最小全域木の重み
+ 元のグラフから辺 e を除去してできるグラフ G - e の最小全域木の重み

とを比較します。これらが異なれば、その辺 e は絶対必要ということになります。

よってすべての辺 e に対して上記の処理を実施すれば解くことができます。

一回の最小全域木の計算には O(M log N) の計算量がかかかりますので、全体の計算量は O(M^2 log N) となります。しかしこれでは計算量がとても大きいです。

　

そこで、まずは一回元のグラフ上で最小全域木 T を求めることにしましょう。

このとき、「絶対必要」な辺は少なくとも T には含まれるはずです。よって、先ほどのように G に含まれるすべての辺 e について調べるのではなく、T に含まれる辺のみを考えればよいです。これによって、調べるべき辺の本数を大きく減らすことができます。

実際 T は木ですので、調べるべき辺の本数は N-1 本です。よって計算量は O(MN log N) へと改善されます。

　

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find
struct UnionFind {
    vector<int> par;

    UnionFind() { }
    UnionFind(int n) : par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) {
        return -par[root(x)];
    }
};

// 辺を表す構造体
using pint = pair<int, int>;  // 両端点
using Edge = pair<long long, pint>;  // (重み, 両端点)

int main() {
    // 入力
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges[i] = Edge(w, pint(u, v));
    }

    // 各辺を重みの小さい順にソート
    sort(edges.begin(), edges.end());

    // id 番目の辺を削除した場合の最小全域木を求める関数
    // id == -1 のときは、通常の最小全域木を求める
    // res は、最小全域木をなす辺番号が格納される
    auto calc = [&](vector<int> &res, int id = -1) -> long long {
        long long cost = 0;
        res.clear();

        // Kruskal 法
        UnionFind uf(N);
        for (int i = 0; i < edges.size(); ++i) {
            if (i == id) continue;
            int u = edges[i].second.first, v = edges[i].second.second;
            if (uf.issame(u, v)) continue;
            res.push_back(i);
            cost += edges[i].first;
            uf.merge(u, v);
        }

        // N-1 本に満たない場合は連結でない
        if (res.size() < N - 1) return (1LL<<60);
        return cost;
    };
    
    // もとのグラフの最小全域木を求める
    vector<int> mst;
    long long base = calc(mst);

    // 最小全域木 mst に含まれる各辺 e を 1 本ずつ除去して調べる
    vector<int> dammy;
    long long num = 0, res = 0;
    for (auto id : mst) {
        if (calc(dammy, id) > base) {
            ++num;
            res += edges[id].first;
        }
    }
    cout << num << " " << res << endl;
}
```

　


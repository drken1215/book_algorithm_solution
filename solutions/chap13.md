# 13.1 (グラフの連結成分数)

まず、深さ優先探索で解いてみましょう。

本文中の code 13.4 に多少の改変を施すことで解くことができます (下コード)。

具体的には、main 関数の中で、すべての頂点 v に対して `seen[v]` が true となるまで、各頂点 v に対して `dfs(v)` を呼び出しています。このとき、すでに `seen[v]` が true となっている頂点に対しては `dfs(v)` は呼び出されません。

よって、各連結成分につき一度だけ、その連結成分に含まれる頂点 v に対して `dfs(v)` が呼び出されることになります。ゆえに、下コードの変数 `result` は、アルゴリズム終了時には「連結成分の個数」を表します。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;

// グラフを表す型
using Graph = vector<vector<int>>;

// 深さ優先探索
vector<bool> seen;
void dfs(const Graph &G, int v) {
    // 頂点 v を訪問済みにする
    seen[v] = true;

    // 頂点 v に隣接する各頂点を探索
    for (auto next_v: G[v]) {
        // 探索済みの頂点は探索しない
        if (seen[next_v]) continue;

        // 再帰的に探索
        dfs(G, next_v);
    }
}

int main() {
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ入力受け取り
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 全頂点が探索済みになるまで DFS
    int result = 0;
    seen.assign(N, false);  // 全頂点を未訪問に初期化
    for (int v = 0; v < N; ++v) {
        // 探索済みの連結成分はスキップする
        if (seen[v]) continue;

        // 頂点 v を始点とした DFS
        dfs(G, v);

        // 連結成分数が増える
        ++result; 
    }

    cout << result << endl;
}
```

　

続いて、幅優先探索で解いてみましょう。深さ優先探索とまったく同様に、全頂点が探索済みになるまで BFS する方針で解いてみましょう。

　

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// グラフを表す型
using Graph = vector<vector<int>>;

// 頂点 s を始点とした BFS
vector<int> dist;  // BFS に用いる距離配列
void bfs(const Graph &G, int s) {
    queue<int> que;

    // 初期条件
    dist[s] = 0;
    que.push(s);

    // キューが空になるまで探索
    while (!que.empty()) {
        // キューから先頭要素を取り出す
        int v = que.front();
        que.pop();

        // 頂点 v に隣接する各頂点を探索
        for (auto next_v: G[v]) {
            // 探索済みの頂点は探索しない
            if (dist[next_v] != -1) continue;

            // 新たな頂点をキューに追加
            dist[next_v] = dist[v] + 1;
            que.push(next_v);
        }
    }
}

int main() {
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ入力受け取り
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 配列 dist 全体を -1 に初期化
    dist.assign(N, -1);

    // 各頂点からの BFS
    int result = 0;
    for (int v = 0; v < N; ++v) {
        // 探索済みの連結成分はスキップする
        if (dist[v] != -1) continue;

        // 頂点 v を始点とした DFS
        bfs(G, v);

        // 連結成分数が増える
        ++result; 
    }

    cout << result << endl;
}
```

　

# 13.2 (s-t パス)

深さ優先探索による解法と同様に、頂点 s を始点とした幅優先探索を行います (下コード)。探索終了後、

- `dist[t] != -1` のとき、s から t へ到達可能であることを表す
- `dist[t] == -1` のとき、s から t へ到達不可能であることを表す

となることがわかります。

　

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// グラフを表す型
using Graph = vector<vector<int>>;

// 頂点 s を始点とした BFS
vector<int> dist;  // BFS に用いる距離配列
void bfs(const Graph &G, int s) {
    queue<int> que;

    // 初期条件
    dist[s] = 0;
    que.push(s);

    // キューが空になるまで探索
    while (!que.empty()) {
        // キューから先頭要素を取り出す
        int v = que.front();
        que.pop();

        // 頂点 v に隣接する各頂点を探索
        for (auto next_v: G[v]) {
            // 探索済みの頂点は探索しない
            if (dist[next_v] != -1) continue;

            // 新たな頂点をキューに追加
            dist[next_v] = dist[v] + 1;
            que.push(next_v);
        }
    }
}

int main() {
    // 頂点数と辺数、s と t
    int N, M, s, t;
    cin >> N >> M >> s >> t;

    // グラフ入力受け取り
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 配列 dist 全体を -1 に初期化して BFS
    dist.assign(N, -1);
    bfs(G, s);

    // t にたどり着けるかどうか
    if (dist[t] != -1) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 13.3 (二部グラフ判定)

code 13.5 と同様に、各頂点の色を管理する配列 `color` を用意して、

- 白色頂点に隣接した頂点は黒色に塗る
- 黒色頂点に隣接した頂点は白色に塗る

という処理を繰り返していきましょう。その過程でもし「両端点が同色であるような辺」が検出されたならば、二部グラフではないことが確定します。

　

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// グラフを表す型
using Graph = vector<vector<int>>;

// 頂点 s を始点とした BFS
vector<int> color;  // 1: 黒色, 0: 白色, -1: 未確定
bool bfs(const Graph &G, int s) {
    queue<int> que;

    // 初期条件
    color[s] = 0;
    que.push(s);

    // キューが空になるまで探索
    bool is_bipartite = true;
    while (!que.empty()) {
        // キューから先頭要素を取り出す
        int v = que.front();
        que.pop();

        // 頂点 v に隣接する各頂点を探索
        for (auto next_v: G[v]) {
            // 隣接頂点がすでに色確定していた場合
            if (color[next_v] != -1) {
                // 同じ色が隣接した場合は二部グラフではない
                if (color[next_v] == color[v]) {
                    is_bipartite = false;
                }
                continue;
            }
            
            // 隣接頂点の色を変更して、キューに push
            color[next_v] = 1 - color[v];
            que.push(next_v);
        }
    }
    return is_bipartite;
}

int main() {
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ入力受け取り
    Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 配列 color 全体を -1 に初期化して BFS
    color.assign(N, -1);
    bool is_bipartite = true;
    for (int v = 0; v < N; ++v) {
        // v が探索済みの場合は探索しない
        if (color[v] != -1) continue;

        // 頂点 v を始点とした BFS
        // もし連結成分が二部グラフでなければ、全体の答えも false
        if (!bfs(G, v)) is_bipartite = false;
    }
    
    if (is_bipartite) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 13.4 (迷路の最短路)

ここでは次のような入力で与えられるものとします。

- 1 行目に迷路のサイズ (縦の長さ, 横の長さ)
- 2 行目以降に迷路の地図 (`S`: スタート, `G`: ゴール, `.`: 通路, `#`: 壁)

マス `S` からマス `G` へと至る最短経路を BFS で求めてみましょう。各マスを頂点とし、マスの隣接関係を辺としたグラフを考えて探索します。

　

```
8 8
.#....#G
.#.#....
...#.##.
#.##...#
...###.#
.#.....#
...#.#..
S.......
```

　

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

// 上下左右への動きを表すベクトル
const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};

int main() {
    // 入力
    int H, W;  // 縦の長さ, 横の長さ
    cin >> H >> W;
    vector<string> field(H);
    for (int i = 0; i < H; ++i) cin >> field[i];

    // スタートとゴールのマスを割り出す
    int sx = -1, sy = -1, gx = -1, gy = -1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (field[i][j] == 'S') sx = i, sy = j;
            if (field[i][j] == 'G') gx = i, gy = j;
        }
    }

    // 各頂点は pair<int,int> 型で表すことにする
    using Node = pair<int,int>;
    queue<Node> que;  // キュー 

    // 初期条件
    // dist[i][j] はマス (i, j) への最短路長を表す
    que.push({sx, sy});
    vector<vector<int>> dist(H, vector<int>(W, -1));
    dist[sx][sy] = 0;

    // BFS 開始
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();

        // 隣接頂点を順にみていく
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 盤面外はスキップ
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;

            // 壁には入れない
            if (field[nx][ny] == '#') continue;

            // 探索済みでなければ新たにキューに追加
            if (dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                que.push(Node(nx, ny));
            }
        }
    }

    // 最短路長
    cout << dist[gx][gy] << endl;
}
```

　

# 13.5 (トポロジカルソート)

13.5 と 13.6 は、応用的な探索となります。BFS でトポロジカルソートを実現する方法としては、

- シンク (終点となる頂点) をキューに追加していく
- シンクを除去して、それによって新たにシンクとなる頂点をキューに追加していく

というものが考えられます。具体的なアルゴリズムや詳細については、次の記事の「3.4 節 トポロジカルソート」に記しましたので、ぜひ参考にしてください。

[BFS (幅優先探索) 超入門！ 〜 キューを鮮やかに使いこなす 〜](https://qiita.com/drken/items/996d80bcae64649a6580)

　

# 13.6 (有向サイクル検出)

有向サイクルが存在する有向グラフ上で DFS を実行した場合、「頂点 v から探索を開始したときに、頂点 v から行くことのできるすべての頂点の探索を終えるよりも先に、頂点 v に戻って来る」という状況が発生し得ることになります。これを検知するために、

- `seen[v]` ← 行きがけ順の意味で v が訪問済みであることを表す (帰りがけ順の意味で v が訪問済みかどうかは定かではない)
- `finished[v]` ← 帰りがけ順の意味で v が訪問済みであることを表す

というデータを用意しましょう。「`seen[v]` = true && `finished[v]` = false」の状態で頂点 v に戻るような状況が発生したならば、「グラフはサイクルを含み、v はサイクル内の頂点である」ということが確定します。

具体的なアルゴリズムや詳細については、次の記事の「4.6 節 サイクル検出」に記しましたので、ぜひ参考にしてください。

[DFS (深さ優先探索) 超入門！ 〜 グラフ・アルゴリズムの世界への入口 〜【後編】](https://qiita.com/drken/items/a803d4fc4a727e02f7ba)

　


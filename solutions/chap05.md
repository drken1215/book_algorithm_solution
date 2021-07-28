# 5.1 (EDPC C - Vacation)

もし「2 日連続で同一種類の選択をできない」という制約がなければ、単純に各日程ごとに `max(a[i], b[i], c[i])` を合計するだけですね。実際は制約があるのでそれに応じた解法を考える必要があります。

次のように配列 `dp` を定義しましょう。

-----

`dp[i][j]` ← 最初の i 日間の分の行動について考えます。i 日間の行動のうち、最後の日の活動が、j = 0 のときは「海での泳ぎ」、j = 1 のときは「虫捕り」、j = 2 のときは「宿題」であるとします。そのときの幸福度の最大値

-----

そして、`dp[i]` から `dp[i+1]` への遷移については、次の 6 通りのパターンを考えます。

- `dp[i][0]` から `dp[i+1][1]`への遷移
- `dp[i][0]` から `dp[i+1][2]`への遷移
- `dp[i][1]` から `dp[i+1][0]`への遷移
- `dp[i][1]` から `dp[i+1][2]`への遷移
- `dp[i][2]` から `dp[i+1][0]`への遷移
- `dp[i][2]` から `dp[i+1][1]`への遷移

次のようにすればよいでしょう。6 本の式を並べて書くのは大変ですので、添字 j, k を用いて for 文ループを回すようにします。

-----

各 (j, k) (j, k = 0, 1, 2, j != k) に対して

`chmax(dp[i+1][k], dp[i][j] + a[i][k]);`

-----

以上をまとめて、次のように実装できます。計算量は O(N) となります。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> void chmax(T& a, T b) { if (a < b) a = b; }
template<class T> void chmin(T& a, T b) { if (a > b) a = b; }

int main() {
    // 入力
    int N; 
    cin >> N;
    vector<vector<long long>> a(N, vector<long long>(3));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < 3; ++j) 
            cin >> a[i][j];

    // DP テーブル
    vector<vector<long long>> dp(N+1, vector<long long>(3, 0));

    // i 日目から i+1 日目へ
    for (int i = 0; i < N; ++i) {
        // i 日目の状態は j、i+1 日目の状態は k
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (j == k) continue;
                chmax(dp[i + 1][k], dp[i][j] + a[i][k]);
            }
        }
    }

    // 答え
    long long res = 0;
    for (int j = 0; j < 3; ++j) chmax(res, dp[N][j]);
    cout << res << endl;
}
```

　

# 5.2 (部分和問題)

5.4 節で解説した「ナップサック問題」とほとんど同様に解くことができます。部分問題を次のように定義します。

-----

`dp[i][j]` ← 最初の i 個の整数の中からいくつか選んだ総和が j にできるかどうかを表すブール値 (true / false)

-----

ナップサック問題とほとんど同様に、解くことができます。ナップサック問題では、`dp[i][0]`, `dp[i][1]`, ... の値が分かっていることを前提に `dp[i+1][0]`, `dp[i+1][1]`, ... の値を求める遷移式を考えました。部分和問題でも同様です。`dp[i+1][j]` の値を考えるときに、`a[i]` を選ぶ場合と選ばない場合とで場合分けして考えます。次のように考えられます。

　

```cpp
// a[i] を選ばない場合
if (dp[i][j]) dp[i+1][j] = true;

// a[i] を選ぶ場合
if (j >= a[i] && dp[i][j-a[i]]) dp[i+1][j] = true;
```

　

これらをまとめると、次のように実装できます。計算量は O(NW) となります。



```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 入力
    int N, W;
    cin >> N >> W;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // DP
    vector<vector<bool>> dp(N+1, vector<bool>(W+1, false));
    dp[0][0] = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            // a[i] を選ばない場合
            if (dp[i][j]) dp[i+1][j] = true;

            // a[i] を選ぶ場合
            if (j >= a[i] && dp[i][j-a[i]]) dp[i+1][j] = true;
        }
    }

    // 答え
    if (dp[N][W]) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.3 (TDPC A - コンテスト)

部分和問題を少し発展させた問題です。部分和問題に対する動的計画法により、O(NW) の計算量で、1, 2, ..., W をそれぞれ作ることができるかを表す配列を作ることができます。これによって、1, 2, ..., W のうち作れる値が何個あるかが求められます。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder TDPC A - コンテスト](https://drken1215.hatenablog.com/entry/2020/12/21/153600)

　

# 5.4 (K 個以内で W を作る)

N 個の整数 `a[0]`, `a[1]`, ..., `a[N-1]` から K 個以内の整数を選んで、総和が W となるようにできるかどうかを判定する問題を考えます。一見すると、O(NKW) の計算量を必要とするように思えるかもしれません。つまり、次のような配列 `dp` を定義することが考えられます。

-----

`dp[i][j][k]` ← 最初の i 個の整数の中から、総和が j がなるように選ぶことができるかどうかを表すブール値 (true / false)。ただし選ぶ個数が k 個以内となるようにする

-----

このような配列の遷移を考えることで、確かにこの問題を解くことができます。たとえば次のコードのようなループを組めばよいでしょう。しかしこのままでは O(NKW) の計算量となってしまいます。

　

```cpp
for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= W; ++j) {
        for (int k = 0; k <= K; ++k) {
            // a[i] を選ばない場合
            if (dp[i][j][k])
                dp[i+1][j][k] = true;
                
            // a[i] を選ぶ場合
            if (j >= a[i] && k >= 1 && dp[i][j-a[i]][k-1])
                dp[i+1][j][k] = true;
        }
    }
}
```

　

しかし実は、次のように配列 `dp` を定義することで解決できます。先ほどの配列 `dp` はブール値であったのに対し、今回の `dp` はより豊かな情報を持たせています。

-----

`dp[i][j]` ← 最初の i 個の整数の中からいくつか選んだ総和が j にする方法のうち、選ぶ整数の個数の最小値

------

遷移自体は今までのナップサック問題や、部分和問題とほとんど同様に考えることができます。

　

```cpp
// a[i] を選ばない場合
chmin(dp[i+1][j], dp[i][j]);

// a[i] を選ぶ場合 (+1 は 1 個増やすことを意味する)
if (j >= a[i]) chmin(dp[i+1][j], dp[i][j-a[i]] + 1);
```

　

そして最後に、`dp[N][W]` が K 以下かどうかによって、目的を果たせるかどうかを判定できます。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> void chmax(T& a, T b) { if (a < b) a = b; }
template<class T> void chmin(T& a, T b) { if (a > b) a = b; }

// 無限大を表す値
const int INF = 1<<29;

int main() {
    // 入力
    int N, K, W;
    cin >> N >> K >> W;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 配列 dp
    vector<vector<int>> dp(N+1, vector<int>(W+1, INF));

    // 初期条件
    dp[0][0] = 0;

    // ループ
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            // a[i] を選ばない場合
            chmin(dp[i+1][j], dp[i][j]);

            // a[i] を選ぶ場合
            if (j >= a[i]) chmin(dp[i+1][j], dp[i][j-a[i]] + 1);
        }
    }

    // 最小値が K 以下ならば、Yes
    if (dp[N][W] <= K) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.5 (個数制限なし部分和問題)

これまでの問題よりも難易度が大きく上がります。次のように配列 dp を定義しましょう。

-----

`dp[i][j]` ← 最初の i 個の整数のみを用いて、重複ありを許して総和をとった値を j にすることが可能かどうか

-----

通常の部分和問題では次のように遷移します。

```cpp
dp[i+1][j] |= dp[i][j];
dp[i+1][j] |= dp[i][j-a[i]];
```

しかし今回は、同じ整数 `a[i]` を何度でも活用することができます。上の遷移式では、`a[i]` を一度しか使えない状態になっています。そこで遷移を次のように変更しましょう。

```cpp
dp[i+1][j] |= dp[i][j];
dp[i+1][j] |= dp[i+1][j-a[i]];
```

このように変更することで、`a[i]` を何度でも活用できる状態になります。計算量は変わらず O(NW) となります。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> void chmax(T& a, T b) { if (a < b) a = b; }
template<class T> void chmin(T& a, T b) { if (a > b) a = b; }

int main() {
    // 入力
    int N, W;
    cin >> N >> W;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // DP テーブル
    vector<vector<bool>> dp(N+1, vector<bool>(W+1, false));

    // 初期条件
    dp[0][0] = true;

    // ループ
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (dp[i][j]) dp[i+1][j] = true;
            if (j >= a[i] && dp[i+1][j-a[i]]) dp[i+1][j] = true;
        }
    }

    // 答え
    if (dp[N][W]) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.6 (個数制限付き部分和問題)

5.5 (個数制限なし部分和問題) よりも難易度が大きく上がります。5.5 では各整数を無制限に用いることができましたが、今回はそれぞれの整数 `a[i]` を活用できる回数の上限 `m[i]` が定められています。そこで、配列 dp の定義を次のように変更します。

------

`dp[i][j]` ← 最初の i 個の整数のみを用いて、整数 j を作る方法のうち、最後の整数を用いる回数の**最小値**

------

このとき、`dp[i]` から `dp[i+1]` への遷移を次のように詰めることができます。なお、j を作ることができない場合は `dp[i][j] = INF` (`INF` を無限大を表す値とする) であるものとします。

　

#### `a[i]` を用いない場合

`dp[i][j] < INF` ならば、`a[i]` を用いずに `j` を作ることができるので、 

`chmin(dp[i+1][j], 0)`

　

#### `dp[i+1][j-a[i]] < m[i]`  である場合

さらに追加で `a[i]` を用いることができるので、

`chmin(dp[i+1][j], dp[i+1][j-a[i]] + 1)`

　

以上の処理を実装すると次のコードになります。計算量は O(NW) です。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> void chmax(T& a, T b) { if (a < b) a = b; }
template<class T> void chmin(T& a, T b) { if (a > b) a = b; }

// 無限大を表す値
const int INF = 1<<29;

int main() {
    // 入力
    int N, W;
    cin >> N >> W;
    vector<int> a(N), m(N);
    for (int i = 0; i < N; ++i) cin >> a[i] >> m[i];

    // DP
    vector<vector<int>> dp(N+1, vector<int>(W+1, INF));

    // 初期条件
    dp[0][0] = 0;

    // ループ
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            // i 個ですでに j が作れる場合
            if (dp[i][j] < INF) chmin(dp[i+1][j], 0);

            // i+1 個で m[i] 個未満で j-a[i] が作れるなら j も作れる
            if (j >= a[i] && dp[i+1][j-a[i]] < m[i]) {
                chmin(dp[i+1][j], dp[i+1][j-a[i]]+1);
            }
        }
    }

    // 答え
    if (dp[N][W] < INF) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.7 (最長共通部分列問題)

本問題は、5.5 節で解説した「編集距離を求める問題」の類題です。編集距離を求める動的計画法と同様に、次の配列 `dp` を定義しましょう。なお、最長共通部分列のことを LCS (Longest Common Subsequence) と呼びます。

-----

`dp[i][j]` ← 文字列 S の最初の i 文字と、文字列 T の最初の j 文字分との間の LCS の長さ

-----

そして、「S の 最初の i 文字分」と「T の最初の j 文字分」のそれぞれの最後の 1 文字をどのように対応付けるかによって場合分けして考えます。

　

#### S の i 文字目と T の j 文字目を対応させるとき

- `S[i-1] == T[j-1]` ならば、`chmax(dp[i][j], dp[i-1][j-1]+1)`
- それ以外ならば、`chmax(dp[i][j], dp[i-1][j-1])`

　

#### S の i 文字目を追加

「S の最初の i - 1 文字分」と「T の最初の j 文字分」との対応に対して、S の i 文字目を追加します。このとき、特に LCS の長さは変わらないので次のようになります。

`chmax(dp[i][j], dp[i-1][j])`

　

#### T の j 文字目を追加

「S の最初の i 文字分」と「T の最初の j - 1 文字分」との対応に対して、T の j 文字目を追加します。このとき、特に LCS の長さは変わらないので次のようになります。

`chmax(dp[i][j], dp[i][j-1])`

　

これらをまとめると、次のように実装できます。計算量は O(NM) となります (N：S の長さ、M：T の長さ)。

　

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
template<class T> void chmax(T& a, T b) { if (a < b) a = b; }
template<class T> void chmin(T& a, T b) { if (a > b) a = b; }

int main() {
    // 入力
    string S, T;
    cin >> S >> T;
    int N = S.size(), M = T.size();

    // DP テーブル
    vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

    // ループ
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            // S の i 文字目と、T の j 文字目が等しいとき
            if (i > 0 && j > 0) {
                if (S[i-1] == T[j-1]) chmax(dp[i][j], dp[i-1][j-1] + 1);
                else chmax(dp[i][j], dp[i-1][j-1]);
            }
          
            // S に 1 文字追加
            if (i > 0) {
                chmax(dp[i][j], dp[i-1][j]);
            }
          
            // T に 1 文字追加
            if (j > 0) {
                chmax(dp[i][j], dp[i][j-1]);
            }
        }
    }

    // LCS
    cout << dp[N][M] << endl;
}
```

　　

# 5.8 (RUPC 2018 day1-D 水槽)

本問題は、5.6 節で解説した「区間分割を最適化する問題」の類題です。この問題の解法については、次の記事で詳しく解説しています。

[AOJ 2877 水槽 (RUPC 2018 day1-D)](https://drken1215.hatenablog.com/entry/2020/12/21/202300)

　

# 5.9 (最適二分探索木問題)

本問題は、最適二分探索木問題と呼ばれている有名問題です。結論から書くと、DP テーブルを次のように定義するとよいです。

------

`dp[i][j]` ←  スライムの大きさを表す配列 `a` の部分配列 `a[i:j]` (`a[i], a[i+1], …, a[j-1]`) についてのみ考えた場合の、スライムが 1 匹になるまで合体させるのに必要な操作のコストの最小値 

------

このとき、DP の遷移は次のように考えます。まず、部分配列 `a[i:j]` のスライムが 1 匹になる直前の状態を考えます。直前の状態では、スライムが 2 匹の状態となっているはずです。この 2 匹のスライムがそれぞれ部分配列 `a[i:k]`,  `a[k:j]` に由来しているものとしましょう。このとき、スライムの合体コストは `dp[i][k] + dp[k][j] + s[i:j] ` となります (`s[i:j]` を、`a[i], a[i+1], …, a[j-1]` の総和とします)。

以上の場合分けを、i < k < j を満たす各 k に対して行います。よって動的計画法による更新部分は次のように表せます (実際には `S[i:j]` という表記は C++ にはないことに注意)。



```cpp
for (int k = i+1; k < j; ++k) {
    chmin(dp[i][j], dp[i][k] + dp[k][j] + s[i:j]);
}
```



最後に、動的計画法による更新順序について考えてみましょう。上の遷移式では、`dp[i][k]` と `dp[k][j]` の値がわかっていることを前提として、`dp[i][j]` の値を更新しています。ここで、k - i と j - k はいずれも j - i より小さい値となっています。よって、配列 `dp[i][j]` を更新するときには、j - i が小さい順に更新していけばよいことがわかります。

以上を踏まえて、次のコードのように実装できます。計算量は O(N^3) となります。なお、配列 `a` の累積和を `S` としています。これは上述の遷移式中の `s[i:j]` の計算をするのに用いています。具体的には `s[i:j] = S[j] - S[i]` と計算できます。累積和について詳しく知りたい方は、次の記事を参照してください。

[累積和を何も考えずに書けるようにする！](https://qiita.com/drken/items/56a6b68edef8fc605821)

　

```cpp
#include <iostream>
#include <vector>
using namespace std;

template<class T> inline bool chmin(T& a, T b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}

// 無限大を表す値
const long long INF = 1LL<<60;

int main() {
    // 入力
    int N;
    cin >> N;
    vector<long long> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 累積和をとる
    vector<long long> S(N+1, 0);
    for (int i = 0; i < N; ++i) S[i+1] = S[i] + a[i];

    // DP
    vector<vector<long long>> dp(N+1, vector<long long>(N+1, INF));

    // 初期条件
    for (int i = 0; i < N; ++i) dp[i][i+1] = 0;

    // 更新
    for (int bet = 2; bet <= N; ++bet) {
        for (int i = 0; i + bet <= N; ++i) {
            int j = i + bet;

            // dp[i][j] を更新する
            for (int k = i+1; k < j; ++k) {
                chmin(dp[i][j], dp[i][k] + dp[k][j] + S[j]-S[i]);
            }
        }
    }

    cout << dp[0][N] << endl;
}
```








# 5.1 (EDPC C - Vacation)

次のように配列 dp を定義します。

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

具体的には次のコードのように実装できます。詳細については以下の記事の「C 問題 - Vacation」の章を読んでみてください。

- [動的計画法超入門！ Educational DP Contest の A ～ E 問題の解説と類題集](https://qiita.com/drken/items/dc53c683d6de8aeacf5a)

　　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

int main() {
    // 入力
    int N; 
    cin >> N;
    vector<vector<long long>> a(N, vector<long long>(3));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < 3; ++j) 
            cin >> a[i][j];

    // DP
    vector<vector<long long>> dp(N+1, vector<long long>(3, 0));
    for (int i = 0; i < N; ++i) {
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

`dp[i][j]` ← 最初の i 個の整数の中からいくつか選んだ総和が j にできるかどうかを表すブール値

-----

ナップサック問題とほとんど同様に、次のようなコードで解決できます。詳細については以下の記事の「問題 3: 部分和問題」の節を読んでみてください。

- [典型的な DP (動的計画法) のパターンを整理 Part 1 ～ ナップサック DP 編 ～](https://qiita.com/drken/items/a5e6fe22863b7992efdb)

　

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
            if (!dp[i][j]) continue;
            dp[i+1][j] = true;
            if (j+a[i] <= W) dp[i+1][j+a[i]] = true;
        }
    }

    // 答え
    if (dp[N][W]) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.3 (TDPC A - コンテスト)

ここでは詳細を省略しますが、部分和問題で求めた配列 dp を活用することで解けます。次の記事で解説しています。

- [AtCoder TDPC A - コンテスト](https://drken1215.hatenablog.com/entry/2020/12/21/153600)

　

# 5.4 (k 個以内で W を作る)

次の配列 dp を求めることで解決できます。

-----

`dp[i][j]` ← 最初の i 個の整数の中からいくつか選んだ総和が j にする方法のうち、選ぶ整数の個数の最小値

------

詳細については以下の記事の「問題 6: K個以内部分和問題」の節を読んでみてください。

- [典型的な DP (動的計画法) のパターンを整理 Part 1 ～ ナップサック DP 編 ～](https://qiita.com/drken/items/a5e6fe22863b7992efdb)

　

# 5.5 (個数制限なし部分和問題)

これまでの問題よりも難易度が大きく上がります。次のように配列 dp を定義します。

-----

`dp[i][j]` ← 最初の i 個の整数のみを用いて、重複ありを許して総和をとった値を j にすることが可能かどうか

-----

通常の部分和問題では次のように遷移します。

　

```cpp
dp[i+1][j] |= dp[i][j];
dp[i+1][j+a[i]] |= dp[i][j];
```

　

しかし今回は、同じ整数 `a[i]` を何度でも活用することができます。上の遷移式では、`a[i]` を一度しか使えない状態になっています。そこで遷移を次のように変更しましょう。

　

```cpp
dp[i+1][j] |= dp[i][j];
dp[i+1][j+a[i]] |= dp[i+1][j];
```

　

このように変更することで、`a[i]` を何度でも活用できる状態になります。計算量は変わらず O(NW) となります。

　

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
            if (dp[i][j]) dp[i+1][j] = true;
            if (dp[i+1][j] && j+a[i] <= W) dp[i+1][j+a[i]] = true;
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



- `a[i]` を用いない場合

`dp[i][j] < INF` ならば、`a[i]` を用いずに `j` を作ることができるので、 

`chmin(dp[i+1][j], 0)`



- `dp[i+1][j] < m[i]`  である場合

さらに追加で `a[i]` を用いることができるので、

`chmin(dp[i+1][j+a[i]], dp[i+1][j] + 1)`



以上の処理を実装すると次のコードになります。計算量は O(NW) です。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

const int INF = 1<<29;
int main() {
    // 入力
    int N, W;
    cin >> N >> W;
    vector<int> a(N), m(N);
    for (int i = 0; i < N; ++i) cin >> a[i] >> m[i];

    // DP
    vector<vector<int>> dp(N+1, vector<int>(W+1, INF));
    dp[0][0] = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (dp[i][j] < INF) chmin(dp[i+1][j], 0);
            if (j+a[i] <= W && dp[i+1][j] < m[i]) {
                chmin(dp[i+1][j+a[i]], dp[i+1][j]+1);
            }
        }
    }

    // 答え
    if (dp[N][W] < INF) cout << "Yes" << endl;
    else cout << "No" << endl;
}
```

　

# 5.7 (最長共通部分列問題)

本問題は、5.5 節で解説した「編集距離を求める問題」の類題です。詳細については、以下の記事の「問題 8: 最長共通部分列 (LCS) 問題」の節に詳しく書きました。

- [典型的な DP (動的計画法) のパターンを整理 Part 1 ～ ナップサック DP 編 ～](https://qiita.com/drken/items/a5e6fe22863b7992efdb)

　　

# 5.8 (RUPC 2018 day1-D 水槽)

本問題は、5.6 節で解説した「区間分割を最適化する問題」の類題です。詳細については、以下の記事で詳しく解説しています。

- [AOJ 2877 水槽 (RUPC 2018 day1-D)](https://drken1215.hatenablog.com/entry/2020/12/21/202300)

　

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

- [累積和を何も考えずに書けるようにする！](https://qiita.com/drken/items/56a6b68edef8fc605821)

　

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








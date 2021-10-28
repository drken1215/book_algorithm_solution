# 6.1 (座標圧縮)

競技プログラミングでは「座標圧縮」と言われている処理です。座標圧縮は、しばしば、より難しい問題の前処理として要求されます。

まず、整数列 `a[0]`, `a[1]`, ..., `a[N-1]` を小さい順にソートしましょう (ソートは O(N log N) でできます、第 12 章参照)。ソートして得られる配列を `b[0]`, `b[1]`, ..., `b[N-1]` とします。このとき、各 `i` に対して、`b[j] = a[i]` となるような index `j` が見つけられればよいことになります。

これは 6.2 節で解説した std::lower_bound を用いて次のように求められます。まず `lower_bound(b.begin(), b.end(), a[i])` によって、配列 `b` 上のイテレータが求められます。これと配列 `b` の先頭を表すイテレータ `b.begin()` との差分をとることで、`b[j] = a[i]` となる index `j` が求められます。

　

```cpp
int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
```

　

各要素 `a[0]`, `a[1]`, ..., `a[N-1]` に対して上記の処理を行うと、全体の計算量は O(N log N) となります。具体的には次のように実装できます。配列 `b` 全体のソートは `sort(b.begin(), b.end()))` によって実現できます。

　

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 入力
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // a をコピーした配列を作ってソートする
    auto b = a;
    sort(b.begin(), b.end());

    // 各 a について b の中で何番目か
    vector<int> res(N);
    for (int i = 0; i < N; ++i) {
        res[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    // 出力
    for (int i = 0; i < N; ++i) cout << res[i] << endl;
}
```

　

# 6.2 (ABC 077 C - Snuke Festival)

まず、配列 `a`, `b`, `c`  をそれぞれソートします。そして配列 `b` の各要素 `b[j]` に対して、`a[i] < b[j]` となる `i` の個数と、`b[j] < c[k]` となる `k` の個数をそれぞれ求めていきます (ここで lower_bound を用います)。より具体的な解法については、次の記事に記しています。

[AtCoder ABC 077 C - Snuke Festival](https://drken1215.hatenablog.com/entry/2021/02/25/223800)

　

# 6.3 (第 7 回 JOI 本選 問3 - ダーツ)

とても難易度の高い問題ですが、「半分全列挙」と「二分探索」の考え方によって解くことができます。この問題の解法については、次の記事に記しています。

[JOI 本選 2018 C - ダーツ](https://drken1215.hatenablog.com/entry/2020/12/04/035454)

　

# 6.4 (POJ No. 2456 Aggressive cows)

最適化問題を解くときには、「判定問題を考えて二分探索ができないか」を考えるアプローチが有効になることがあります (6.7 節参照)。今回の問題では、次のような判定問題を考えてみましょう。

-----

N 個の小屋から M 個を選ぶ。このとき、どの 2 つの小屋の間隔も x 以上離れている状態にすることは可能か？

-----

元の問題の答えは「上記の判定問題の答えが Yes であるような最大の x」になります。よって、上記の判定問題を解くことができれば、二分探索法によって答えが求められます。具体的にはまず、変数 `left` , `right` を用意して、

- `left` の初期値を 0 (答えが確実に Yes となる)
- `right` の初期値を INF (答えが確実に No となるような値 INF を定めておく)

とします。そして、`x = (left + right) / 2` としてあげて、x について上記の判定問題を解きます。そして、

- 判定問題の答えが Yes のときは、`left ← x`
- 判定問題の答えが No のときは、`right ← x`

とすればよいです。

最後に、判定問題の解き方を考えましょう。判定問題は小屋を左から順番に見ていって「最後に選んだ小屋から x 以上離れたらその小屋を選んで行く」というふうにすればよいです (7 章で学ぶ貪欲法の一種です)。具体的な処理内容については、以下のコードを参考にしてみてください。判定問題が O(N) の計算量で解けますので、全体の計算量は O(N log A) (A を小屋間の距離の最大値とする) となります。

なお下の実装では、簡単のため、変数 `right` の初期値を「十分大きな値」を表す `INF` としていますので、正確な計算量は O(N log INF) となっています。

　

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 十分大きな値
const long long INF = 1LL<<50;

int main() {
    // 入力
    int N, M;
    cin >> N >> M;
    vector<long long> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    // 「すべての間隔を x 以上にして M 個の小屋を選べるか？」という判定問題を解く
    // Yes であるような最大の x を求める
    long long left = 0, right = INF;
    while (right - left > 1) {
        long long x = (left + right) / 2;

        int cnt = 1; // 何個の小屋が取れたか (最初の小屋は選ぶ)
        int prev = 0; // 前回の小屋の index
        for (int i = 0; i < N; ++i) {
            // x 以上の間隔が空いたら採用する
            if (a[i] - a[prev] >= x) {
                ++cnt;
                prev = i;
            }
        }

        // 判定問題が Yes か No か
        if (cnt >= M) left = x;
        else right = x;
    }
    cout << left << endl;
}
```

　

# 6.5 (ARC 037 C - 億マス計算)

「K 番目に小さな値を求めよ」「メディアンを求めよ」という設定の問題では、しばしば二分探索法が有効となります。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ARC 037 C - 億マス計算](https://drken1215.hatenablog.com/entry/2021/07/03/041500)

　

# 6.6 (ABC 026 D - 高橋君ボール 1 号)

方程式 f(t) = 0 の解を求めるタイプの問題ですね。そのような問題では二分探索法が有効となることがあります (そのような場合、二分法と呼ぶこともあります)。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 026 D - 高橋君ボール1号](https://drken1215.hatenablog.com/entry/2021/07/03/173400)

　

# 6.7 (ARC 101 D - Median of Medians)

「K 番目に小さな値を求めよ」「メディアンを求めよ」という設定の問題では、しばしば二分探索法が有効となります。大変難しい問題です。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 107 D - Median of Medians](https://drken1215.hatenablog.com/entry/2018/09/08/011500?_ga=2.135966193.1107495987.1625194483-791597362.1625194483)


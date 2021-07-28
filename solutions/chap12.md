# 12.1

さまざまな方法が考えられます。ここではソーティング後に二分探索 (lower_bound()) を用いる方法を考えてみましょう。

まず配列 `a` をソートしてできる配列を `b` としましょう (配列 `a` 自体には変更を加えないようにしておきます)。このとき、`a` の各要素 `a[i]` に対して

　　`lower_bound(b.begin(), b.end(), a[i]) - b.begin()`

を取得することで、`a[i]` が `b` の中で何番目の要素かが求められます (0-indexed)。計算量は

- ソートする部分：$O(N \log N)$
- 各要素に対して二分探索する部分：$O(N \log N)$

によって、全体として $O(N \log N)$ となります。

　

```cpp
#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // 入力
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // ソート
    auto b = a;
    sort(b.begin(), b.end());

    // 各要素について二分探索
    for (int i = 0; i < N; ++i) {
        cout << lower_bound(b.begin(), b.end(), a[i]) - b.begin() << endl;
    }
}
```

　

# 12.2

N 個のお店のうち、どのような順序で回ればよいかを考えましょう。基本的には価格の安い (`A[i]` が小さい) お店から順に回ればよいでしょう。

そこでまず、価格が安い順に、N 個のお店を並べ替えましょう。この処理は O(N log N) の計算量でできます。そしてこの並びの順に、購入数が M に達するまで、お店を回っていきましょう。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 121 C - Energy Drink Collector](https://drken1215.hatenablog.com/entry/2019/05/15/012700)

　

# 12.3

ヒープを活用します。次の 2 種類のヒープを用意しましょう。

- サイズ k 




















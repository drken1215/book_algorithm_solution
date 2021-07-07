# 3.1

仮に i = 2, 5, 9 に対して a[i] == v であったとします。このとき、

- まず i = 2 に対して、`found_id = i` の処理によって、found_id = 2 となります
- 次に i = 5 に対して、`found_id = i` の処理によって、found_id = 5 となります
- 最後に i = 9 に対して、`found_id = i` の処理によって、found_id = 9 となります

このように、a[i] == v を満たす i が新たに見つかるたびに、found_id の値がそれに書き換わります。よって最終的な found_id の値は、 a[i] = v を満たす i のうち、最大のものとなります。



　

# 3.2

次のような実装によって求めることができます。a[i] == v となる i が見つかるたびにインクリメントする変数を用意します。計算量は O(N) です。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 入力を受け取る
    int N, v;
    cin >> N >> v;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 線形探索
    int counter = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] == v) {
            ++counter;  // カウントを増やす
        }
    }

    // 結果出力
    cout << counter << endl;
}
```



　

# 3.3

次の 2 つの変数を用意します。

- 最小値を表す変数 `worst_value`
- 2 番目に小さな値を表す変数 `second_value`

これらを用いて、次のように実装できます。計算量は O(N) です。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 20000000;   // 十分大きな値に

int main() {
    // 入力を受け取る
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 線形探索
    int worst_value = INF;
    int second_value = INF;
    for (int i = 0; i < N; ++i) {
        if (a[i] < worst_value) {
            second_value = worst_value;
            worst_value = a[i];
        }
        else if (a[i] < second_value) second_value = a[i];
    }

    // 結果出力
    cout << second_value << endl;
}
```



　

# 3.4

N 個の値の「最大値」と「最小値」を求めます。それらの差が求める値となります。計算量は O(N) です。

　

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 20000000;   // 十分大きな値に

int main() {
    // 入力を受け取る
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 線形探索
    int max_value = -INF;
    int min_value = INF;
    for (int i = 0; i < N; ++i) {
        if (a[i] < min_value) min_value = a[i];
        if (a[i] > max_value) max_value = a[i];
    }

    // 結果出力
    cout << max_value - min_value << endl;
}
```



　

# 3.5 (ABC 081 B - Shift Only)

たとえば、a = (8, 12, 40)​ の場合を考えてみますと

- 8 は 2 で 3 回割り切れます
- 12 は 2 で 2 回割り切れます
- 40 は 2 で 3 回割り切れます

この中で最小回数である 12 (2 回) が全体のボトルネックになることがわかります。つまり操作可能回数は 2 回となります。このことから、次の解法が考えられます。

------

N 個の整数 a[0], a[1], …, a[N-1] に対して、それぞれ「2 で何回割れるか」を求めます。そのうちの最小値が答えになります。

-----

　

```cpp
#include <iostream>
#include <vector>
using namespace std;

// N が 2 で何回割れるか
int how_many_times(int N) {
    int exp = 0;
    while (N % 2 == 0) N /= 2, ++exp;
    return exp;
}

// 無限大を表す値
const int INF = 1234567890;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    // 2 で何回割れるかの最小値を求める
    int result = INF;
    for (auto a : A) {
        result = min(result, how_many_times(a));
    }
    cout << result << endl;
}
```



　

# 3.6 (ABC 051 B - Sum of Three Integers)

最初に次のような全探索解法が思い浮かぶかもしれません。

　

```cpp
int counter = 0;
for (int X = 0; X <= K; ++X) {
    for (int Y = 0; Y <= K; ++Y) {
        for (int Z = 0; Z <= K; ++Z) {
            if (X + Y + Z == N) ++counter;
        }
    }
}
```

　

しかしこのままですと、O(K^3) の計算量となってしまいます。そこで、X + Y + Z = N という関係式に着目します。実は、X, Y の 2 つの値を決めたとき、



Z = N - X - Y



というように、Z の値はただ一つに決まります。この値が 0 <= Z <= K を満たすとは限りませんが、少なくとも Z = N - X - Y でなければなりません。そして、0 <= Z <= K を満たすかどうかを確認します。満たしたならば、個数を表す変数 `counter` をインクリメントします。

以上をまとめて、次のように実装できます。なお、添字 X のとる範囲を「X <= K」から「X <= min(K, N)」へと改良しています (添字 Y も同様)。計算量は、M = min(K, N) として、O(M^2) となります。

　

```cpp
#include <iostream>
using namespace std;

int main() {
    int K, N;
    cin >> K >> N;

    int count = 0;
    for (int x = 0; x <= min(K, N); ++x) {
        for (int y = 0; y <= min(K, N); ++y) {
            int z = N - x - y;
            if (z >= 0 && z <= K) {
                ++count;
            }
        }
    }
    cout << count << endl;
}
```



　

# 3.7 (ABC 045 C - たくさんの数式)

3.5 節で解説した「整数の二進法表現とビット演算」を活用します。長さ N の文字列 S の「隙間」は N-1 箇所あります。そのそれぞれについて

+ 「+」を入れる
+ 「+」を入れない

という 2 つの選択肢があります。よってすべての選択肢は 2^(N-1) 通りとなります。「部分和問題」と同様に、これらの選択肢を 0 以上 2^(N-1) 未満の整数値 (変数 bit) で管理します。

少々実装が複雑ですが、次のように実装できます。計算量は O(N2^N) となります。

　

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string S;
    cin >> S;
    int N = S.size();

    // N-1 箇所の隙間に「+」を入れるかどうかをすべて試す
    long long res = 0;
    for (int bit = 0; bit < (1<<(N-1)); ++bit) {
        // tmp：「+」と「+」との間の値を表す変数
        long long tmp = 0;
        for (int i = 0; i < N-1; ++i) {
            tmp *= 10;
            tmp += S[i] - '0';

            // 「+」を挿入するとき、答えに tmp を加算して、tmp を 0 に初期化
            if (bit & (1<<i)) {
                res += tmp;
                tmp = 0;
            }
        }

        // 最後の「+」から残りの部分を答えに加算
        tmp *= 10;
        tmp += S.back() - '0';
        res += tmp;
    }
    cout << res << endl;
}
```










# 2.1

次のように表せます。

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/sol2-1.png height=210mm>



　

# 2.2

0 <= i < j < k < N を満たす (i, j, k) の組の個数を数え上げればよいでしょう。これは、N 個のものから 3 個を選ぶ場合の数に等しいので、

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/sol2-2.png height=60mm>

となります。よって、計算量は O(N^3) と評価できます。



　

# 2.3

p × p <= N を満たす p の個数を数え上げればよいでしょう。p <= √N となることから、計算量は O(√N) と評価できます。



　

# 2.4

A さんの年齢の選択肢は、1 回の質問によって半減させることができます。たとえば A さんの年齢の選択肢が 2^5 通りであった場合には、次のように 5 回の質問によって A さんの年齢の選択肢は 1 通りになります。



- 初期状態：2^5 = 32 通りの選択肢
- 1 回目の質問後：2^4 = 16 通りの選択肢
- 2 回目の質問後：2^3 = 8 通りの選択肢
- 3 回目の質問後：2^2 = 4 通りの選択肢
- 4 回目の質問後：2^1 = 2 通りの選択肢
- 5 回目の質問後：2^0 = 1 通りの選択肢 (ただ 1 通りに限られた状態)



同様に、A さんの年齢の選択肢が 2^k 通りであった場合には、k 回の質問によって 1 通りに絞ることができます。以上のことを厳密に証明したいと考えた場合には、数学的帰納法を用いればよいでしょう。



　

# 2.5

まず、整数 k を用いて N = 2^k と表せる場合を考えます (たとえば N = 1024 などです)。このとき、k = log N であることに注意します。問題 2.4 から、k 回の質問によって当てられることが示されましたので、O(log N) 回の質問で当てられることがわかります。

一般の整数 N に対しては、次のように考えます。まず、

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/sol2-5-1.png height=70mm>

を満たすような整数 k が定まることに注意します。たとえば N = 100 のとき、k = 7 となります (2^6 = 64、2^7 = 128 です)。このとき、k < log N + 1 ですので、k = O(log N) です。一方、N <= 2^k より、k 回の質問によって当てることができます。以上より、O(log N) 回の質問によって、A さんの年齢を当てられることがわかりました。



　

# 2.6

下のグラフより、次の式が成り立ちます。

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/sol2-6-2.png height=75mm>

これは、1 + 1/2 + … + 1/N = O(log N) であることを示しています。

　

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/sol2-6-1.png width=500mm>

　


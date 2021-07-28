# 11.1 (ABC 075 C - Bridge)

Union-Find を有効活用できるよい練習問題です。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 075 C - Bridge](https://drken1215.hatenablog.com/entry/2021/07/27/165300)

　

# 11.2 (ABC 120 D - Decayed Bridges)

一般に、グラフの辺を削除したときにグラフがどのように変化していくかを調べることは難しいです。そこで、グラフ全体から辺を 1 本ずつ削除していくのではなく、グラフが空の状態から 1 本ずつ追加するものとして考えてみましょう。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 120 E - Decayed Bridges](https://drken1215.hatenablog.com/entry/2019/03/03/224600)

　

# 11.3 (ABC 049 D - 連結)

「道路」と「鉄道」の 2 種類が登場するのが難しいです。これに対応するために、道路用の Union-Find と、鉄道用の Union-Find というように、Union-Find を 2 つ用意して考えましょう。具体的なアルゴリズムについては、次の記事に記しています。

[AtCoder ABC 049 D - 連結](https://drken1215.hatenablog.com/entry/2021/07/28/014400)

　

# 11.4 (ABC 087 D - People on a Line)

さまざまな解法が考えられる問題です。ここでは、Union-Find の各頂点に「各都市の相対的な位置関係」を表す重みを付けて考える解法を紹介します。これを実現するためには**重み付き Union-Find** とよばれるデータ構造を活用します。重み付き Union-Find の詳細の解説と、この問題の解説については、次の記事に記しています。

[重み付き Union-Find 木とそれが使える問題のまとめ、および、牛ゲーについて](https://qiita.com/drken/items/cce6fc5c579051e64fab)

　




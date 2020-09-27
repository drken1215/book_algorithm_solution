# 概要

本レポジトリは，拙著『問題解決力を鍛える!アルゴリズムとデータ構造』(以下，「本書」とよびます) の補足資料です．以下の内容を掲載しています．

- 本書で掲載しているソースコード (codes フォルダ以下)
- 本書の各章の章末問題への略解 (solutions フォルダ以下)

　

https://www.amazon.co.jp/dp/4065128447

<img src=https://github.com/drken1215/book_algorithm_solution/blob/master/fig/book_image.png width=250mm>

　

# 使用言語と動作環境

本書では，C++ を用いてアルゴリズムを記述していきます．
ただし，以下のような C++11 以降の機能を一部用います．

- 範囲 for 文
- auto を用いた型推論 (範囲 for 文においてのみ用います)
- 「`std::vector<int> v = \{ 1, 2, 3 \};`」といった vector 型変数の初期化
- using を用いた型エイリアスの宣言
- テンプレートの右山カッコに空白を入れなくてもよいこと
- `std::sort()` の計算量が O(N log N) であることが仕様として保証されていること

本書のソースコードの多くは，C++11 以降のバージョンの C++ を利用している場合のみコンパイル可能なものとなっていることに注意してください．なお，本書で掲載している C++ のソースコードは，すべて Wandbox 上の gcc 9.2.0 で動作するものとなっています．　

　

# 注意事項・今後の予定

章末問題の略解は、現在は簡潔な記述にとどめていますが、今後コンテンツを充実させていく予定です。また、各 C++ ソースコードと同等の処理を Python でも提供していく予定です。

　


# License

These codes are licensed under CC0.

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png "CC0")](http://creativecommons.org/publicdomain/zero/1.0/deed.ja)
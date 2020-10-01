#include <iostream>
#include <vector>
using namespace std;

// 配列 a をソートする
void InsertionSort(vector<int> &a) {
    int N = (int)a.size();
    for (int i = 1; i < N; ++i) {
        int v = a[i]; // 挿入したい値

        // v を挿入する適切な場所 j を探す
        int j = i;
        for (; j > 0; --j) {
            if (a[j-1] > v) { // v より大きいものは 1 つ後ろに移す
                a[j] = a[j-1];
            }
            else break; // v 以下になったら止める
        }
        a[j] = v; // 最後に j 番目に v をもってくる
    }
}

int main() {
    // 入力
    int N; // 要素数
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 挿入ソート
    InsertionSort(a);
}

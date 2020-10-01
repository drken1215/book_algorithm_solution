#include <iostream>
#include <vector>
using namespace std;

// 配列 a の区間 [left, right) をソートする
// [left, right) は，left, left+1, ..., right-1 番目を表す
void MergeSort(vector<int> &a, int left, int right) {
    if (right - left == 1) return;
    int mid = left + (right - left) / 2;

    // 左半分 [left, mid) をソート
    MergeSort(a, left, mid);

    // 右半分 [mid, right) をソート
    MergeSort(a, mid, right);

    // いったん「左」と「右」のソート結果をコピーしておく (右側は左右反転)
    vector<int> buf;
    for (int i = left; i < mid; ++i) buf.push_back(a[i]);
    for (int i = right - 1; i >= mid; --i) buf.push_back(a[i]);

    // 併合する
    int index_left = 0;                    // 左側の添字
    int index_right = (int)buf.size() - 1; // 右側の添字
    for (int i = left; i < right; ++i) {
        // 左側採用
        if (buf[index_left] <= buf[index_right]) {
            a[i] = buf[index_left++];
        }
        // 右側採用
        else {
            a[i] = buf[index_right--];
        }
    }
}

int main() {
    // 入力
    int N; // 要素数
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // マージソート
    MergeSort(a, 0, N);
}

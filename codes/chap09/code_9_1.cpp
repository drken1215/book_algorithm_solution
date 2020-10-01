#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100000; // スタック配列の最大サイズ

int st[MAX]; // スタックを表す配列
int top = 0; // スタックの先頭を表す添字

// スタックを初期化する
void init() {
    top = 0; // スタックの添字を初期位置に
}

// スタックが空かどうかを判定する
bool isEmpty() {
    return (top == 0); // スタックサイズが 0 かどうか
}

// スタックが満杯かどうかを判定する
bool isFull() {
    return (top == MAX); // スタックサイズが MAX かどうか
}

// push
void push(int x) {
    if (isFull()) {
        cout << "error: stack is full." << endl;
        return;
    }
    st[top] = x; // x を格納して
    ++top; // top を進める
}

// pop
int pop() {
    if (isEmpty()) {
        cout << "error: stack is empty." << endl;
        return -1;
    }
    --top; // top をデクリメントして
    return st[top]; // top の位置にある要素を返す
}

int main() {
    init(); // スタックを初期化

    push(3); // スタックに 3 を挿入する {} -> {3}
    push(5); // スタックに 5 を挿入する {3} -> {3, 5}
    push(7); // スタックに 7 を挿入する {3, 5} -> {3, 5, 7}

    cout << pop() << endl; // {3, 5, 7} -> {3, 5} で 7 を出力
    cout << pop() << endl; // {3, 5} -> {3} で 5 を出力

    push(9); // 新たに 9 を挿入する {3} -> {3, 9}
}

#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100000; // キュー配列の最大サイズ

int qu[MAX]; // キューを表す配列
int tail = 0, head = 0; // キューの要素区間を表す変数

// キューを初期化する
void init() {
    head = tail = 0;
}

// キューが空かどうかを判定する
bool isEmpty() {
    return (head == tail);
}

// キューが満杯かどうかを判定する
bool isFull() {
    return (head == (tail + 1) % MAX);
}

// enqueue
void enqueue(int x) {
    if (isFull()) {
        cout << "error: queue is full." << endl;
        return;
    }
    qu[tail] = x;
    ++tail;
    if (tail == MAX) tail = 0; // リングバッファの終端に来たら 0 に
}

// dequeue
int dequeue() {
    if (isEmpty()) {
        cout << "error: queue is empty." << endl;
        return -1;
    }
    int res = qu[head];
    ++head;
    if (head == MAX) head = 0; // リングバッファの終端に来たら 0 に
    return res;
}

int main() {
    init(); // キューを初期化

    enqueue(3); // キューに 3 を挿入する {} -> {3}
    enqueue(5); // キューに 5 を挿入する {3} -> {3, 5}
    enqueue(7); // キューに 7 を挿入する {3, 5} -> {3, 5, 7}

    cout << dequeue() << endl; // {3, 5, 7} -> {5, 7} で 3 を出力
    cout << dequeue() << endl; // {5, 7} -> {7} で 5 を出力

    enqueue(9); // 新たに 9 を挿入する {7} -> {7, 9}
}

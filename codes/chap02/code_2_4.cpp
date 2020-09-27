#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 2 点 (x1, y1) と (x2, y2) との距離を求める関数
double calc_dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    // 入力データを受け取る
    int N; cin >> N;
    vector<double> x(N), y(N);
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
    
    // 求める値を、十分大きい値で初期化しておく
    double minimum_dist = 100000000.0;
    
    // 探索開始
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            // (x[i], y[i]) と (x[j], y[j]) との距離
            double dist_i_j = calc_dist(x[i], y[i], x[j], y[j]);
            
            // 暫定最小値 minimum_dist を dist_i_j と比べる
            if (dist_i_j < minimum_dist) {
                minimum_dist = dist_i_j;
            }
        }
    }
    
    // 答えを出力する
    cout << minimum_dist << endl;
}

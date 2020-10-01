#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<long long> F(50);
    F[0] = 0, F[1] = 1;
    for (int N = 2; N < 50; ++N) {
        F[N] = F[N - 1] + F[N - 2];
        cout << N << " ¹àÌÜ: " << F[N] << endl;
    }
}

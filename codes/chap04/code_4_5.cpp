int fibo(int N) {
    // ベースケース
    if (N == 0) return 0;
    else if (N == 1) return 1;

    // 再帰呼び出し
    return fibo(N - 1) + fibo(N - 2);
}

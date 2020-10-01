int root(int x) {
    if (par[x] == -1) return x; // x が根の場合は x を直接返す
    else return root(par[x]); // x が根でないなら再帰的に親へと進む
}

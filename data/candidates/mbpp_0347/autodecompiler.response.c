int func0(int n, int k) {
    if (k < n) {
        int tmp = n;
        n = k;
        k = tmp;
    }
    return k*(k+1)*(3*n-k+1)/6;
}
int nCr(int n, int r, int mod) {
    if (r > n-r) r = n-r;
    int C[n-r+1];
    int i, j;
    for (i = 0; i <= r; ++i)
        C[i] = 0;
    C[0] = 1;
    for (i = 1; i <= n; ++i) {
        j = ((i)<(r)?(i):(r));
        while (j > 0) {
            C[j] = (C[j] + C[j-1])%mod;
            --j;
        }
    }
    return C[r];
}
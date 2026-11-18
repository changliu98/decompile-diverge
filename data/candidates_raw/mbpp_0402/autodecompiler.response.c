int nCr(int n, int r, int mod) {
    int Pascal[r + 1];
    int i, j;
    for (i = 0; i <= r; ++i)
        Pascal[i] = 0;

    Pascal[0] = 1;

    for (i = 1; i <= n; ++i) {
        int k = ((i)<(r)?(i):(r));
        for (j = k; j > 0; --j)

            Pascal[j] = (Pascal[j] + Pascal[j-1]) % mod;
    }
    return Pascal[r];
}
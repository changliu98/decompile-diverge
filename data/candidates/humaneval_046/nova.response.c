int func0(int n) {
    int f[100];
    int i;
    f[0] = 0;
    f[1] = 0;
    for (i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2] + f[i - 3] + f[i - 4];
    }
    return f[n];
}
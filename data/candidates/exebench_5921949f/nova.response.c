void factorial(double f[2 * K + 1][2 * K + 1]) {
    int i;
    f[K][K] = 1;
    for (i = 0; i < 2 * K; i++)
        f[i][i + 1] = (i + 1) * 1.;
}
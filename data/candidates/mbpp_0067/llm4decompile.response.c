unsigned_long_long func0(int n)
{
    int i, j;
    unsigned_long_long **bell;
    unsigned_long_long ret;

    bell = (unsigned_long_long **)malloc(sizeof(unsigned_long_long *) * (n + 1));
    for (i = 0; i <= n; i++) {
        bell[i] = (unsigned_long_long *)malloc(sizeof(unsigned_long_long) * (n + 1));
        for (j = 0; j <= n; j++)
            bell[i][j] = 0;
    }

    bell[0][0] = 1;
    for (i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        for (j = 1; j <= i; j++)
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
    }

    ret = bell[n][0];

    for (i = 0; i <= n; i++)
        free(bell[i]);
    free(bell);

    return ret;
}
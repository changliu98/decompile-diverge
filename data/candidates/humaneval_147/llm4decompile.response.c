int func0(int n)
{
    int i, j, k, l, times, ans;
    int *a = malloc((long long)n * sizeof(int));
    int **sum = malloc((long long)(n + 1) * sizeof(int *));
    int **sum2 = malloc((long long)(n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        sum[i] = calloc(3, sizeof(int));
        sum2[i] = calloc(3, sizeof(int));
    }
    sum[0][2] = 0;
    sum[0][1] = 0;
    sum[0][0] = 0;
    sum2[0][2] = 0;
    sum2[0][1] = 0;
    sum2[0][0] = 0;
    for (i = 1; i <= n; i++) {
        a[i - 1] = (i * i - i + 1) % 3;
        for (j = 0; j < 3; j++)
            sum[i][j] = sum[i - 1][j];
        sum[i][a[i - 1]]++;
    }
    for (times = 1; times <= 2; times++) {
        for (i = 1; i <= n; i++) {
            for (j = 0; j < 3; j++)
                sum2[i][j] = sum2[i - 1][j];
            if (i > 0)
                for (j = 0; j < 3; j++)
                    sum2[i][(j + a[i - 1]) % 3] += sum[i - 1][j];
        }
        for (i = 0; i <= n; i++) {
            for (j = 0; j < 3; j++) {
                sum[i][j] = sum2[i][j];
                sum2[i][j] = 0;
            }
        }
    }
    ans = sum[n][0];
    for (i = 0; i <= n; i++) {
        free(sum[i]);
        free(sum2[i]);
    }
    free(sum);
    free(sum2);
    free(a);
    return ans;
}
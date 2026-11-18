int func0(int *arr, int N, int K)
{
    qsort(arr, (size_t)N, sizeof(int), cmpfunc);
    int *dp = malloc(sizeof(int) * N);
    dp[0] = 0;
    for (int i = 1; i < N; i++)
    {
        dp[i] = dp[i - 1];
        if (arr[i] - arr[i - 1] < K)
        {
            if (i >= 2)
                dp[i] = ((dp[i - 2] + arr[i - 1] + arr[i]) < (dp[i]) ? (dp[i - 2] + arr[i - 1] + arr[i]) : (dp[i]));
            else
                dp[i] = ((arr[i - 1] + arr[i]) < (dp[i]) ? (arr[i - 1] + arr[i]) : (dp[i]));
        }
    }
    int res = dp[N - 1];
    free(dp);
    return res;
}
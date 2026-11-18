int __cdecl func0(int *arr, int n)
{
    int dp[/* n */];   // VLA: dp[i] = longest valid subsequence ending at i
    int result;
    int i, j;

    // Base case: every single element forms a subsequence of length 1.
    for (i = 0; i < n; ++i)
        dp[i] = 1;

    // DP transition: try to extend a previous subsequence ending at j (< i)
    // if |arr[i] - arr[j]| == 1.
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < i; ++j)
        {
            if ((arr[i] == arr[j] + 1 || arr[i] == arr[j] - 1)
                && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // Answer is the maximum value in dp[].
    result = 1;
    for (i = 0; i < n; ++i)
    {
        if (result < dp[i])
            result = dp[i];
    }
    return result;
}
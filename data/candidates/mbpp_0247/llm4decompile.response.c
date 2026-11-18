int func0(char *str)
{
    int i, j, k, len;
    int dp[200][200];
    len = strlen(str);
    for (i = 0; i < len; i++)
        dp[i][i] = 1;
    for (k = 2; k <= len; k++)
    {
        for (i = 0; i < len - k + 1; i++)
        {
            j = i + k - 1;
            if (str[i] == str[j] && k == 2)
                dp[i][j] = 2;
            else if (str[i] == str[j])
                dp[i][j] = 2 + dp[i + 1][j - 1];
            else
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1] ? dp[i + 1][j] : dp[i][j - 1]);
        }
    }
    return dp[0][len - 1];
}
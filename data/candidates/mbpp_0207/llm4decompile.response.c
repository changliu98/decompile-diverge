int func0(char *str)
{
    int i, j, len;
    int dp[200][200];
    len = strlen(str);
    for (i = 0; i <= len; i++)
        for (j = 0; j <= len; j++)
            dp[i][j] = 0;
    for (i = 1; i <= len; i++)
        for (j = 1; j <= len; j++)
            if (str[i - 1] == str[j - 1] && i != j)
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
    return dp[len][len];
}
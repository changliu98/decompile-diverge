char *func0(char *s) {
    int len = strlen(s);
    if (len == 0) {
        char *res = (char *)malloc(1);
        if (res)
            *res = '\0';
        return res;
    }
    int i, j, k;
    int dp[256];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < len; i++)
        dp[s[i]]++;
    char *res;
    for (i = 0; i < 3; i++) {
        res = (char *)malloc(len + 1);
        if (res) {
            j = 0;
            for (k = 0; k < 256; k++)
                if (dp[k] > 0) {
                    res[j++] = k;
                    dp[k]--;
                }
            res[j] = '\0';
        }
    }
    return res;
}
int func0(int arr[], int n, int m)
{
    if (n > m)
        return 1;
    char DP[m];
    for (int i = 0; i < m; i++)
        DP[i] = 0;
    for (int i = 0; i < n; i++)
    {
        if (DP[0] % 2)
            return 1;
        char temp[m];
        for (int j = 0; j < m; j++)
            temp[j] = 0;
        for (int j = 0; j < m; j++)
            if (DP[j] % 2 && !DP[(j + arr[i]) % m] % 2)
                temp[(j + arr[i]) % m] = 1;
        for (int j = 0; j < m; j++)
            if (temp[j] % 2)
                DP[j]++;
        DP[arr[i] % m]++;
    }
    if (DP[0] % 2)
        return 1;
    return 0;
}
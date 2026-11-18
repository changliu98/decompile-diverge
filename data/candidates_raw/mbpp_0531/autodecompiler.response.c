int func0(int* coins, int m, int sum) {
    if (sum == 0)
        return 0;

    int min = 0x7fffffff;
    int i;
    for (i = 0; i < m; ++i) {
        if (coins[i] <= sum) {
            int temp = func0(coins, m, sum - coins[i]);
            if (temp != 0x7fffffff && temp + 1 < min) {
                min = temp + 1;
            }
        }
    }

    return min;
}
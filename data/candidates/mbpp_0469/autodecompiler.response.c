int func0(int *prices, int prices_size, int k) {
    int memo[k+1][prices_size];
    int i, j, l;

    for (i = 0; i <= k; ++i) {
        for (j = 0; j < prices_size; ++j) {
            if (i == 0 || j == 0)
                memo[i][j] = 0;
            else {
                int max = memo[i-1][j-1];
                int curr;

                for (l = 0; l < j; ++l) {
                    curr = prices[j] - prices[l] + memo[i-1][l];
                    if (curr > max)
                        max = curr;
                }

                memo[i][j] = ((memo[i][j-1]) > (max) ? (memo[i][j-1]) : (max));
            }
        }
    }

    return memo[k][prices_size-1];
}
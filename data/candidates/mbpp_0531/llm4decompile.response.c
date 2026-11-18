int func0(int coins[], int m, int V) {
    int res;
    if (V == 0) {
        res = 0;
    } else {
        res = 2147483647;
        for (int i = 0; i < m; i++) {
            if (coins[i] <= V) {
                int sub_res = func0(coins, m, V - coins[i]);
                if (sub_res != 2147483647 && sub_res + 1 < res)
                    res = sub_res + 1;
            }
        }
    }
    return res;
}
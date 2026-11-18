int func0(int n) {
    int i, j, k, cnt = 0;
    for (i = 1; i <= n; i++) {
        for (j = i; j != 0; j /= 2) {
            if (j % 2 == 0) {
                cnt++;
            }
        }
    }
    return cnt;
}
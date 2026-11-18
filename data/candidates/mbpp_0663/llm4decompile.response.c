int func0(int n, int x, int y) {
    int i;
    int ans;
    ans = -2147483648;
    for (i = 0; i <= n; i++) {
        if (i % x == y) {
            if (ans < i) {
                ans = i;
            }
        }
    }
    if (ans < 0 || ans > n) {
        ans = -1;
    }
    return ans;
}
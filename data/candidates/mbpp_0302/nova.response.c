int func0(int n) {
    int i;
    int ans;
    if (n == 0) {
        ans = 0;
    } else {
        for (i = 0; n > 0; i++) {
            n /= 2;
        }
        ans = 1 << (i - 1);
    }
    return ans;
}
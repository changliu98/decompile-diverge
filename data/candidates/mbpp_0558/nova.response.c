int func0(int a, int b) {
    int ans = 0;
    int d = abs(a - b);
    while (d > 0) {
        ans += d % 10;
        d /= 10;
    }
    return ans;
}
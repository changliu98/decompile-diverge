int func0(int n) {
    int x = 1;
    for (int i = 2; i <= n; i++) {
        x *= i;
        while (x % 10 == 0) {
            x /= 10;
        }
    }
    while (x >= 10) {
        x /= 10;
    }
    return (int)floor((double)x);
}
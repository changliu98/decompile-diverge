int func0(int n) {
    int a, b, c, i, sum;
    if (n <= 2) {
        sum = n;
    } else {
        a = 1;
        b = 2;
        for (i = 3; i <= n; i++) {
            sum = a + b * 2;
            a = b;
            b = sum;
        }
    }
    return sum;
}
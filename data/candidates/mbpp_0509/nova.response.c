int func0(int n) {
    int a, b, c;
    if (n % 2 == 0) {
        printf("2^%d-1=%d\n", n, (int)pow(2, n) - 1);
        c = -1;
    } else {
        a = 0;
        b = 0;
        while (n >= 2) {
            b++;
            a = a + n;
            n = n - 2;
        }
        c = a / b;
    }
    return c;
}
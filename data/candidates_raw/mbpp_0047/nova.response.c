int func0(int a, int b) {
    int i, j, k, l, m, n;
    int res;

    res = 1;
    if (a == b) {
        res = 1;
        goto func0_end;
    }
    if (b - a < 6) {
        res = 0;
        goto func0_end;
    }
    for (i = a + 1; i <= b; i++) {
        n = i;
        n %= 10;
        n *= (i - 1) % 10;
        n %= 10;
    }
    res = n % 10;
func0_end:
    return res;
}
int func0(int n) {
    int i, j, k;
    if (n < 2) {
        k = 0;
    } else if (n == 2) {
        k = 1;
    } else {
        k = 18;
        for (i = 2; i < n; i++) {
            k *= 10;
        }
    }
    return k;
}
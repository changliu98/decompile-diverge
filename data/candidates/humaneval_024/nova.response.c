int func0(int n) {
    int i, j;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            j = n / i;
            break;
        }
    }
    return j;
}
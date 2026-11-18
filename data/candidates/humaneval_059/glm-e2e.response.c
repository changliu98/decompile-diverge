int func0(int n) {
    int i = 2;
    while (i * i <= n) {
        while (n % i == 0 && n > i) {
            n = n / i;
        }
        i++;
    }
    return n;
}
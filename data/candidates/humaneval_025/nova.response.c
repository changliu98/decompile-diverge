int *func0(int n, int *len) {
    int *primes = (int *)malloc(256 * sizeof(int));
    int i, j;
    *len = 0;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            n /= i;
            primes[(*len)++] = i;
            i--;
        }
    }
    if (n > 1)
        primes[(*len)++] = n;
    return primes;
}
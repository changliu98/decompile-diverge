int * func0(int n, int *count) {
    int i, j;
    int *primes = malloc(sizeof(int) * n);
    *count = 0;
    for (i = 2; i < n; i++) {
        int isprime = 1;
        for (j = 0; j < *count; j++) {
            if (primes[j] * primes[j] > i) break;
            if (i % primes[j] == 0) {
                isprime = 0;
                break;
            }
        }
        if (isprime) {
            primes[*count] = i;
            *count = *count + 1;
        }
    }
    return primes;
}
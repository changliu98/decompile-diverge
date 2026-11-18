int *func0(int n, int *size) {
    int *primes = (int *)malloc(n * sizeof(int));
    int i, j, isprime, nextprime;
    *size = 0;

    for (i = 2; i < n; i = nextprime) {
        isprime = 1;
        for (j = 0; j < *size; j++) {
            if (primes[j] * primes[j] > i) {
                break;
            }
            if (i % primes[j] == 0) {
                isprime = 0;
                break;
            }
        }
        if (isprime) {
            primes[(*size)++] = i;
        }
        nextprime = i + 1;
        while (1) {
            if (nextprime % 2 == 0) {
                nextprime++;
            } else if (nextprime % 3 == 0) {
                nextprime += 2;
            } else {
                break;
            }
        }
    }

    return primes;
}
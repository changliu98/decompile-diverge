int* func0(int n, int* count) {
    int* primes = malloc(n * sizeof(int));
    *count = 0;
    
    for (int i = 2; i < n; i++) {
        int is_prime = 1;
        for (int j = 0; j < *count; j++) {
            int p = primes[j];
            if (p * p > i) {
                break;
            }
            if (i % p == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            primes[*count] = i;
            (*count)++;
        }
    }
    
    return primes;
}
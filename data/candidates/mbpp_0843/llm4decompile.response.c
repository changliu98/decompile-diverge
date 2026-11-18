long long func0(int n, int *primes, int primesSize) {
    long long *values = malloc((long long)n * sizeof(long long));
    int *indices = calloc((long long)primesSize, sizeof(int));
    long long *uglies = malloc((long long)primesSize * sizeof(long long));
    values[0] = 1;
    for (int i = 0; i < primesSize; i++) {
        uglies[i] = primes[i];
    }
    for (int i = 1; i < n; i++) {
        long long next_ugly = uglies[0];
        for (int j = 1; j < primesSize; j++) {
            if (uglies[j] < next_ugly) {
                next_ugly = uglies[j];
            }
        }
        values[i] = next_ugly;
        for (int j = 0; j < primesSize; j++) {
            if (uglies[j] == next_ugly) {
                indices[j]++;
                uglies[j] = values[indices[j]] * (long long)primes[j];
            }
        }
    }
    long long ret = values[n - 1];
    free(values);
    free(indices);
    free(uglies);
    return ret;
}
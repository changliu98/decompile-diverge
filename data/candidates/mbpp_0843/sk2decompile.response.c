long nthUglyNumber(int n, int* primes, int primesSize) {
  long* ugly = malloc(n * sizeof(long));
  int* index = calloc(primesSize, sizeof(int));
  long* next = malloc(primesSize * sizeof(long));
  ugly[0] = 1;
  for (int i = 0; i < primesSize; i++) {
    next[i] = primes[i];
  }
  for (int i = 1; i < n; i++) {
    long min = next[0];
    for (int j = 1; j < primesSize; j++) {
      if (next[j] < min) {
        min = next[j];
      }
    }
    ugly[i] = min;
    for (int j = 0; j < primesSize; j++) {
      if (next[j] == min) {
        index[j]++;
        next[j] = primes[j] * ugly[index[j]];
      }
    }
  }
  long result = ugly[n - 1];
  free(ugly);
  free(index);
  free(next);
  return result;
}
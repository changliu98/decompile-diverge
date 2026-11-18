

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



int cmp(const void *a, const void *b) {

    long long num1 = *(const long long*)a;

    long long num2 = *(const long long*)b;

    return (num1 > num2) - (num1 < num2); 

}



long long func0(int n, int* primes, int primesSize) {
  long long* uglies = malloc(n * sizeof(long long));
  int* indices = calloc(primesSize, sizeof(int));
  long long* values = malloc(primesSize * sizeof(long long));
  int i, j;
  uglies[0] = 1;
  for (i = 0; i < primesSize; i++) {
    values[i] = primes[i];
  }
  for (i = 1; i < n; i++) {
    long long next_ugly = values[0];
    for (j = 1; j < primesSize; j++) {
      if (values[j] < next_ugly) next_ugly = values[j];
    }
    uglies[i] = next_ugly;
    for (j = 0; j < primesSize; j++) {
      if (values[j] == next_ugly) values[j] = primes[j] * uglies[++indices[j]];
    }
  }
  long long result = uglies[n - 1];
  free(uglies);
  free(indices);
  free(values);
  return result;
}

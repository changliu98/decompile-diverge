long func0(int n, int *primes, int primesSize)
{
  long *uglies = (long *)malloc(sizeof(long)*n);
  int *indices = (int *)calloc(primesSize, sizeof(int));
  long *values = (long *)malloc(sizeof(long)*primesSize);
  int i; int j;
  uglies[0] = 1;
  for (i = 0; i < primesSize; i++)
    values[i] = primes[i];
  for (i = 1; i < n; i++)
  {
    long next_ugly = values[0];
    for (j = 1; j < primesSize; j++)
      if (values[j] < next_ugly)
        next_ugly = values[j];
    uglies[i] = next_ugly;
    for (j = 0; j < primesSize; j++)
      if (values[j] == next_ugly)
      {
        values[j] = uglies[indices[j]++ + 1] * primes[j];
      }
  }
  long result = uglies[n - 1];
  free(uglies);
  free(indices);
  free(values);
  return result;
}
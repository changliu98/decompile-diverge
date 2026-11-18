int *func0(int n, int *count)
{
  int *out;
  int i; int j; int k;
  out = (int *)malloc(n*sizeof(int));
  *count = 0;
  for (i = 2; i < n; i++) {
    int isprime = 1;
    for (j = 0; j < *count; j++) {
      k = out[j];
      if (k * k > i) break;
      if (i % k == 0) {
        isprime = 0;
        break;
      }
    }
    if (isprime) {
      out[*count] = i;
      (*count)++;
    }
  }
  return out;
}
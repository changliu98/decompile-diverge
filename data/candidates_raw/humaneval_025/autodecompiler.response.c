int *prime_factors(int n, int *nf) {
  int *factors = (int *)malloc(64*sizeof(int));
  int p=2;
  *nf = 0;
  while(p*p <= n) {
    while(n % p == 0) {
      n /= p;
      factors[(*nf)++] = p;
    }
    p++;
  }
  if(n > 1)
    factors[(*nf)++] = n;
  return factors;
}
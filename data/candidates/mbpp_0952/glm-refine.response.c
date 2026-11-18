int __cdecl func0(int n, int r, int p)
{
  int *C;
  int j;
  int k;
  int i;
  int limit;

  // Optimization: Use the property C(n, r) == C(n, n - r) to minimize the array size and loop iterations
  if (r > n - r)
    r = n - r;

  // Allocate Variable Length Array (VLA) for the binomial coefficients row
  C = (int *)alloca((r + 1) * sizeof(int));

  // Initialize the array to 0
  for (i = 0; i <= r; ++i)
    C[i] = 0;

  // Base case for the triangle
  C[0] = 1;

  // Build Pascal's triangle up to the n-th row
  for (i = 1; i <= n; ++i)
  {
    // The inner loop only needs to go up to min(i, r)
    if (i >= r)
      limit = r;
    else
      limit = i;

    // Compute the current row backwards to safely use values from the previous row
    for (j = limit; j > 0; --j)
      C[j] = (C[j - 1] + C[j]) % p;
  }

  // The result is the r-th value of the n-th row in Pascal's triangle modulo p
  return C[r];
}
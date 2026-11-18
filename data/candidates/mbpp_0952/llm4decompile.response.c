uint64_t func0(int n, int r, int p)
{
 int i, j;
 uint64_t C[r + 1];

 if (r > n - r)
  r = n - r;

 for (i = 0; i <= r; i++)
  C[i] = 0;
 C[0] = 1;

 for (i = 1; i <= n; i++) {
  int bound = (i < r) ? i : r;
  for (j = bound; j > 0; j--)
   C[j] = (C[j] + C[j - 1]) % p;
 }

 return C[r];
}
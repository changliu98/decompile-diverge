uint64_t func0(uint32_t n, uint32_t r, uint64_t p)
{
 uint64_t C[r+1];
 uint32_t i, j;

 for (i = 0; i <= r; i++)
  C[i] = 0;
 C[0] = 1;

 for (i = 1; i <= n; i++) {
  for (j = ((i) < (r) ? (i) : (r)); j > 0; j--)
   C[j] = (C[j] + C[j-1]) % p;
 }

 return C[r];
}
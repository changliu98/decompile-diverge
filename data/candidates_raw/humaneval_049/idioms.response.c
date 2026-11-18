int powmod(int n, int p)
{
  int i; int out = 1;
  for (i = 0; i < n; i++)
    out = (out * 2) % p;
  return out;
}
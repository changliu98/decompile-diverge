long bin_coff(int n, int k)
{
  return bin_coff(n / 2 * 2, n / 2) / (n / 2 + 1);
}
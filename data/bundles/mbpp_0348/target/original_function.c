long func0(int M) {
  int n = M / 2;
  long a = bin_coff(2 * n, n);
  long b = a / (n + 1);
  return b;
}
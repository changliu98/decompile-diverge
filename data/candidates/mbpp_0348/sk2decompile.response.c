int func0(int n) {
  int k = n / 2;
  int bin_coff_2k = bin_coff(2 * k, k);
  return bin_coff_2k / (k + 1);
}
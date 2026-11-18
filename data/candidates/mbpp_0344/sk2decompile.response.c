int func0(int n, int m) {
  int sqrt_m, sqrt_n_1;
  sqrt_m = (int)sqrt((double)m);
  sqrt_n_1 = (int)sqrt((double)(n - 1));
  return sqrt_m - sqrt_n_1;
}
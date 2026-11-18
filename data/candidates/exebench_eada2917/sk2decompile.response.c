int HPCC_factor235(int n, int *f) {
  f[2] = 0;
  f[1] = 0;
  f[0] = 0;
  if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
    if (n < 2) return 1;
    while (n > 1 && n % 2 == 0) {
      f[0]++;
      n /= 2;
    }
    while (n > 1 && n % 3 == 0) {
      f[1]++;
      n /= 3;
    }
    while (n > 1 && n % 5 == 0) {
      f[2]++;
      n /= 5;
    }
    if (n == 1) return 0;
    return 1;
  }
  return 1;
}
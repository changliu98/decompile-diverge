int _factorial_mod_order(int p) {
  int f = 1;
  int i;
  for (i = 1; i < p; i++) {
    f *= i;
    if (f % p == 0) return i;
  }
  return i - 1;
}
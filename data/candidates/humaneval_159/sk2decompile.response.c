void _add_mod(int a, int b, int m, int *r) {
  if (b > m) {
    r[0] = a + m;
    r[1] = 0;
  } else {
    r[0] = a + b;
    r[1] = m - b;
  }
}
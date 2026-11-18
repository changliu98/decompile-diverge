void func0(int *a, int n) {
  int i, j, t, c, x, y, z;
  for (j = 0; j < n; j++) {
    for (i = j + 1; i < n; i++) {
      c = 0;
      x = a[j];
      y = a[i];
      while (x > 0) {
        c += x & 1;
        x >>= 1;
      }
      z = c;
      c = 0;
      while (y > 0) {
        c += y & 1;
        y >>= 1;
      }
      if (c < z || (c == z && a[i] < a[j])) {
        t = a[j];
        a[j] = a[i];
        a[i] = t;
      }
    }
  }
}
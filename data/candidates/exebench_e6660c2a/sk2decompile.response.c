void foo(int *a, int b, int c) {
  int d = a[0];
  int e = a[1];
  int i;
  for (i = 0; i < 1; i++) {
    a[2 + i] = (b != 0) | (c != 0) | (d != 0) | (1 >> i != 0) | (e != 0);
  }
}
void test1(short n, int *a) {
  short i;
  i = 0;
  while (i < n) {
    i = i + 1;
    a[i] = 0;
  }
}
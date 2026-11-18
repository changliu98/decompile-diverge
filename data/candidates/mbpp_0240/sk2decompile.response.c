void func0(int *a, int na, int *b, int nb, int *c) {
  int i, j;
  for (i = 0; i < na - 1; i++) {
    c[i] = a[i];
  }
  for (j = 0; j < nb; j++) {
    c[na - 1 + j] = b[j];
  }
}
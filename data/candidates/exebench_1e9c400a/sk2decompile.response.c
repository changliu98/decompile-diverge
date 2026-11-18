void myArrayDiv(float *a, float b, float *c) {
  int i;
  for (i = 0; i < 5; i++) {
    c[i] = a[i] / b;
  }
}
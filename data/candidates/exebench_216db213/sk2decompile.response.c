void swapminusfloat(double *a, double *b) {
  *a = *a - *b;
  *b = *a + *b;
  *a = *b - *a;
}
void measure(long x, int *y, int *z, int *a, int *b) {
  *y = *z = x = 63360;
  *z = x * 0.0833333;
  *a = x * 0.0277778;
  *b = x * 0.0000158;
}
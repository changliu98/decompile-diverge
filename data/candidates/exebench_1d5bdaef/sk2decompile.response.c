int foo(float *a, int b) {
  if ((a[0] > 0.0) != (a[1] > 0.0)) {
    b = 0;
  }
  return b;
}
float foo(float *a) {
  a[9] = 56.2343;
  float b = a[9];
  return b;
}
void factorial(double *f) {
  int i;
  f[0] = 1.0;
  for (i = 0; i < 20; i++) {
    f[i + 1] = (i + 1) * f[i];
  }
}
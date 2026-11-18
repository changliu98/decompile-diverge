float avg12(float *x, float *w, unsigned int n) {
  float sum = 0;
  unsigned int i;
  for (i = 0; i < n; i++) {
    sum += x[i] * w[i] * x[i];
  }
  return sum / (n / 2 + n % 2);
}
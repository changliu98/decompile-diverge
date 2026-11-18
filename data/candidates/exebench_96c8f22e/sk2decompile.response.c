void pa(float *x, float a, float b) {
  long i;
  for (i = 0; i < 6; i++) {
    x[0] = (x[0] + x[1] + x[2] - x[3]) * a;
    x[1] = (x[0] + x[1] - x[2] + x[3]) * a;
    x[2] = (x[0] - x[1] + x[2] + x[3]) * a;
    x[3] = (-x[0] + x[1] + x[2] + x[3]) / b;
  }
}
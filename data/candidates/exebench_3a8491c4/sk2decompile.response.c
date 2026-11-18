void Calc_Sum_Mean(double *x, double *sum, double *mean) {
  int i;
  *sum = 0.0;
  for (i = 0; i < 100; i++) {
    *sum += x[i];
  }
  *mean = *sum / 100.0;
}
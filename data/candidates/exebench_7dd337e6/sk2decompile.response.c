void kahan_summation_step(double x, double *sum, double *c, double *y,
                          double *t) {
  *y = x - *c;
  *t = *sum + *y;
  *c = *t - *sum - *y;
  *sum = *t;
}
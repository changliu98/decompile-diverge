void computeRates(double t, double y[], double f[], double rpar[],
                  double ipar[]) {
  f[0] = -1.0 * y[1];
  f[1] = 1.0 * y[0];
}
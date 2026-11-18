void YvVfilterCoef(double fc, double *coef) {
  double a = 1.10783;
  double b = 1.40586;
  double c = 1.1668;
  double a2, b2, f;
  a2 = a * a;
  b2 = b * b;
  if (fc < 3.556) {
    f = -0.2568 + 0.5784 * fc + 0.0561 * fc * fc;
  } else {
    f = 2.5091 + 0.9804 * (fc - 3.556);
  }
  double f2 = f * f;
  double denom = f * (2.0 * a * f + a2 + b2 + f2);
  coef[0] = -f2 * f / denom;
  coef[1] = -f2 * (3.0 * f + 2.0 * a) / denom;
  coef[2] = -f * (2.0 * c * a + 4.0 * f * a + 3.0 * f2) / denom;
  coef[3] = c * (a2 + b2) / denom;
  coef[4] = -f * (2.0 * c * a + 4.0 * f * a + 3.0 * f2) / denom;
  coef[5] = -f2 * (3.0 * f + 2.0 * a) / denom;
  coef[6] = -f2 * f / denom;
}
void FindDivDiff5Coeff2(double x0, double x1, double x2, double x3,
                        double *coeff) {
  double dx01 = 1.0 / (x1 - x0);
  double dx02 = 1.0 / (x2 - x0);
  double dx12 = 1.0 / (x2 - x1);
  double dx03 = 1.0 / (x3 - x0);
  double dx13 = 1.0 / (x3 - x1);
  double dx23 = 1.0 / (x3 - x2);
  coeff[0] = -dx01 * dx01 * dx02 * dx02 * dx03;
  coeff[1] = -(2.0 * dx12 + dx13 - dx01) * dx01 * dx13 * dx12 * dx12;
  coeff[2] = -dx01 * dx13 * dx12 * dx12;
  coeff[3] = -(dx23 - 2.0 * dx12 - dx02) * dx23 * dx02 * dx12 * dx12;
  coeff[4] = -dx23 * dx02 * dx12 * dx12;
  coeff[5] = dx03 * dx13 * dx13 * dx23 * dx23;
}
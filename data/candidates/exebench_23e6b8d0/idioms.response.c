void lincomb(double k1, double u[3], double k2, double v[3], double w[3])
{
  w[0] = k1 * u[0] + k2 * v[0];
  w[1] = k1 * u[1] + k2 * v[1];
  w[2] = k1 * u[2] + k2 * v[2];
}
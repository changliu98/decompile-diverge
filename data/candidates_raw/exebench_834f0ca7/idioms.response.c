void ddd(double a, double b, double c, double *ddd)
{
  double ba = 1 / (b - a);
  double ca = 1 / (c - a);
  double cb = 1 / (c - b);
  ddd[1] = ba * ba * ca * ca;
  ddd[0] = 2 * (ba + ca) * ddd[1];
  ddd[3] = cb * cb * ba * ba;
  ddd[2] = 2 * (ba - cb) * ddd[3];
  ddd[5] = cb * cb * ca * ca;
  ddd[4] = -2 * (ca + cb) * ddd[5];
}
int shape_tria6(double *c, double *d)
{
  double c1 = c[0];
  double c2 = c[1];
  double c3 = 1 - c1 - c2;
  d[0] = c1 * (2 * c1 - 1);
  d[1] = 4 * c1 * c2;
  d[2] = c2 * (2 * c2 - 1);
  d[3] = 4 * c2 * c3;
  d[4] = c3 * (2 * c3 - 1);
  d[5] = 4 * c1 * c3;
  return 0;
}
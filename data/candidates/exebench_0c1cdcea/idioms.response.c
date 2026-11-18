void TriggsM(double *filter, double M[9])
{
  double a1 = filter[0];
  double a2 = filter[1];
  double a3 = filter[2];
  double scale = 1.0 / ((a1 - a2 - a3 + 1.0) * (a1 + a2 + a3 - 1.0) * (a1 * a3 + a2 + 1.0));
  M[0] = scale * (a1 * a3 + a1 * a1 + a1 - a2);
  M[1] = scale * (a1 * a1 + a1 * a3 + a1 * a2);
  M[2] = scale * (a1 * a2 + a1 * a3);
  M[3] = scale * (a1 * a2 + a1 * a1);
  M[4] = scale * (a1 * a1 - a2 * a2);
  M[5] = scale * (a1 * a1 * a3 - a1 * a2 * a2);
  M[6] = scale * (a1 * a1 * a1 + a1 * a1 * a2 + a1 * a3);
  M[7] = scale * (a1 * a1 * a1 * a3 + a1 * a1 * a2 * a2 - a1 * a1 * a1 * a2 - a1 * a1 * a1 * a3);
  M[8] = scale * (a1 * a2 + a1 * a3);
}
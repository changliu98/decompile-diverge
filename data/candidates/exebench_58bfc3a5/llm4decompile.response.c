void FindDivDiff4Coeff(double x1, double x2, double x3, double x4, double x5,
   double *dd)
{
  dd[0] = 1.0 / ((x1 - x2) * (x1 - x3) * (x1 - x4) * (x1 - x5));
  dd[1] = 1.0 / ((x2 - x1) * (x2 - x3) * (x2 - x4) * (x2 - x5));
  dd[2] = 1.0 / ((x3 - x1) * (x3 - x2) * (x3 - x4) * (x3 - x5));
  dd[3] = 1.0 / ((x4 - x1) * (x4 - x2) * (x4 - x3) * (x4 - x5));
  dd[4] = 1.0 / ((x5 - x1) * (x5 - x2) * (x5 - x3) * (x5 - x4));
}
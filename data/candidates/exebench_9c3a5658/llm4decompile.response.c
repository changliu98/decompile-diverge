void cmatrix_from_frame(double m[3][3], const double x[3],
   const double y[3], const double z[3])
{
  int i;
  for (i = 0; i < 3; i++) {
    m[i][0] = x[i];
    m[i][1] = y[i];
    m[i][2] = z[i];
  }
}
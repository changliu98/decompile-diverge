void cmatrix_from_frame(double c[3][3], const double x[3], const double y[3],
                        const double z[3]) {
  int i;
  for (i = 0; i < 3; i++) {
    c[i][0] = x[i];
    c[i][1] = y[i];
    c[i][2] = z[i];
  }
}
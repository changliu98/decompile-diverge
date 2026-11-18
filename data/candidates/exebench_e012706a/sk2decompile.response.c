void cmatrix_to_frame(const double cmatrix[3][3], double x[3], double y[3],
                      double z[3]) {
  int i;
  for (i = 0; i < 3; i++) {
    x[i] = cmatrix[i][0];
    y[i] = cmatrix[i][1];
    z[i] = cmatrix[i][2];
  }
}
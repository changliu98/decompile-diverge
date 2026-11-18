static void icvDetMatrix3x3_64d(const double* a, double* det) {
  double d = a[0] * (a[4] * a[8] - a[5] * a[7]) -
             a[1] * (a[3] * a[8] - a[5] * a[6]) +
             a[2] * (a[3] * a[7] - a[4] * a[6]);
  *det = d;
}
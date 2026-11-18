void geom_matinv2d(double A[2][2]) {
 double det_inv = 1.0 / (A[0][0] * A[1][1] + ((A[0][1] * A[1][0]) * -1.0));
 double tmp = A[0][0];
 A[0][0] = det_inv * A[1][1];
 A[0][1] = det_inv * -1.0 * A[0][1];
 A[1][0] = det_inv * -1.0 * A[1][0];
 A[1][1] = det_inv * tmp;
}
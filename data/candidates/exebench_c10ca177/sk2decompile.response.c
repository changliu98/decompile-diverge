void geom_matinv2d(double *m) {
  double d = 1.0 / (m[0] * m[3] - m[1] * m[2]);
  double t = m[0];
  m[0] = m[3] * d;
  m[1] = -m[1] * d;
  m[2] = -m[2] * d;
  m[3] = t * d;
}
void geom_matinv2d(double m[4]) {
  double a, b, c, d, det;
  a = m[0];
  b = m[1];
  c = m[2];
  d = m[3];
  det = 1.0 / (a * d - b * c);
  m[0] = d * det;
  m[1] = -b * det;
  m[2] = -c * det;
  m[3] = a * det;
}
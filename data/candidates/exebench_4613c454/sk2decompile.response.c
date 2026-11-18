void cquat_scale(double *q, double s, const double *r) {
  q[0] = s * r[0];
  q[1] = s * r[1];
  q[2] = s * r[2];
  q[3] = s * r[3];
}
void cquat_sub(double *q, const double *r, const double *s) {
  q[0] = r[0] - s[0];
  q[1] = r[1] - s[1];
  q[2] = r[2] - s[2];
  q[3] = r[3] - s[3];
}
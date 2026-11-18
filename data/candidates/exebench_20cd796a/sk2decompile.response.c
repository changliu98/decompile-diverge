void cquat_add(double *q, const double *q1, const double *q2) {
  q[0] = q1[0] + q2[0];
  q[1] = q1[1] + q2[1];
  q[2] = q1[2] + q2[2];
  q[3] = q1[3] + q2[3];
}
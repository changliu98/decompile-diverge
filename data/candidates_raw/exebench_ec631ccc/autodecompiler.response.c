void matvec3(double *v1, double *vout, double *m, double *v) {
  vout[0] = m[0]*v1[0] + m[5]*v1[1] + m[4]*v1[2] + v[0];
  vout[1] = m[1]*v1[1] + m[3]*v1[2] + v[1];
  vout[2] = m[2]*v1[2] + v[2];
}
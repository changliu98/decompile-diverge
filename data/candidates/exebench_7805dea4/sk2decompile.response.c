void mlVectorMultMatrixTo(const float *v, const float *m, float *vout) {
  vout[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + m[12];
  vout[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + m[13];
  vout[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];
}
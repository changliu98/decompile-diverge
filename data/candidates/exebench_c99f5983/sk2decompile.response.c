void Mat4_T(float *m) {
  float t;
  t = m[1];
  m[1] = m[4];
  m[4] = t;
  t = m[2];
  m[2] = m[8];
  m[8] = t;
  t = m[3];
  m[3] = m[12];
  m[12] = t;
  t = m[6];
  m[6] = m[9];
  m[9] = t;
  t = m[7];
  m[7] = m[13];
  m[13] = t;
  t = m[11];
  m[11] = m[14];
  m[14] = t;
}
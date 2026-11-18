void Mat4_affine_inv(float *m) {
  float x, y, z;
  float t;
  t = m[0];
  m[0] = m[4];
  m[4] = t;
  t = m[1];
  m[1] = m[8];
  m[8] = t;
  t = m[2];
  m[2] = m[9];
  m[9] = t;
  t = m[6];
  m[6] = m[9];
  m[9] = t;
  x = m[0] * m[12] + m[4] * m[13] + m[8] * m[14];
  y = m[1] * m[12] + m[5] * m[13] + m[9] * m[14];
  z = m[2] * m[12] + m[6] * m[13] + m[10] * m[14];
  m[12] = -x;
  m[13] = -y;
  m[14] = -z;
}
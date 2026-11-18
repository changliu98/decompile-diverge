void Mat4_vec3_mul(float *dst, const float *m, const float *v) {
  float x = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];
  float y = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];
  float z = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];
  dst[0] = x;
  dst[1] = y;
  dst[2] = z;
}
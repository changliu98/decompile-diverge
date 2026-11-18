void mat3f_rotateQuatVec_new(float *dst, const float *q) {
  float qsqr = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
  float s = 2.0f / qsqr;
  float xs = q[0] * s;
  float ys = q[1] * s;
  float zs = q[2] * s;
  float wx = q[3] * xs;
  float wy = q[3] * ys;
  float wz = q[3] * zs;
  float xx = q[0] * xs;
  float xy = q[0] * ys;
  float xz = q[0] * zs;
  float yy = q[1] * ys;
  float yz = q[1] * zs;
  float zz = q[2] * zs;
  dst[0] = 1.0f - (yy + zz);
  dst[3] = xy - wz;
  dst[6] = xz + wy;
  dst[1] = xy + wz;
  dst[4] = 1.0f - (xx + zz);
  dst[7] = yz - wx;
  dst[2] = xz - wy;
  dst[5] = yz + wx;
  dst[8] = 1.0f - (xx + yy);
}
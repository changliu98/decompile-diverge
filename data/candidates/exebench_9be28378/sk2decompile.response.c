void mat3d_rotateQuatVec_new(double *dst, const double *q) {
  double s = 2.0 / (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
  double xs = q[0] * s, ys = q[1] * s, zs = q[2] * s;
  double wx = q[3] * xs, wy = q[3] * ys, wz = q[3] * zs;
  double xx = q[0] * xs, xy = q[0] * ys, xz = q[0] * zs;
  double yy = q[1] * ys, yz = q[1] * zs;
  double zz = q[2] * zs;
  dst[0] = 1.0 - (yy + zz);
  dst[3] = xy - wz;
  dst[6] = xz + wy;
  dst[1] = xy + wz;
  dst[4] = 1.0 - (xx + zz);
  dst[7] = yz - wx;
  dst[2] = xz - wy;
  dst[5] = yz + wx;
  dst[8] = 1.0 - (xx + yy);
}
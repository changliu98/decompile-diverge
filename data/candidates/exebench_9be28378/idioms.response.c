void mat3d_rotateQuatVec_new(double m[9], double q[4])
{
  double s = 2.0 / (q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
  double xs = q[0] * s; double ys = q[1] * s; double zs = q[2] * s;
  double wx = q[3] * xs; double wy = q[3] * ys; double wz = q[3] * zs;
  double xx = q[0] * xs; double xy = q[0] * ys; double xz = q[0] * zs;
  double yy = q[1] * ys; double yz = q[1] * zs; double zz = q[2] * zs;
  m[0] = 1 - (yy + zz);
  m[3] = xy - wz;
  m[6] = xz + wy;
  m[1] = xy + wz;
  m[4] = 1 - (xx + zz);
  m[7] = yz - wx;
  m[2] = xz - wy;
  m[5] = yz + wx;
  m[8] = 1 - (xx + yy);
}
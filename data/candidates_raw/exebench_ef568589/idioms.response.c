void quat2mat(float *mat, float *quat)
{
  float s;
  float xs; float ys; float zs;
  float wx; float wy; float wz;
  float xx; float xy; float xz;
  float yy; float yz; float zz;
  s = 2.0 / (quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3]);
  xs = quat[0]*s;
  ys = quat[1]*s;
  zs = quat[2]*s;
  wx = quat[3]*xs;
  wy = quat[3]*ys;
  wz = quat[3]*zs;
  xx = quat[0]*xs;
  xy = quat[0]*ys;
  xz = quat[0]*zs;
  yy = quat[1]*ys;
  yz = quat[1]*zs;
  zz = quat[2]*zs;
  mat[0] = 1.0 - (yy + zz);
  mat[3] = xy - wz;
  mat[6] = xz + wy;
  mat[1] = xy + wz;
  mat[4] = 1.0 - (xx + zz);
  mat[7] = yz - wx;
  mat[2] = xz - wy;
  mat[5] = yz + wx;
  mat[8] = 1.0 - (xx + yy);
}
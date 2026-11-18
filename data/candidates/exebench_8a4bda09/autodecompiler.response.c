void rsQuat_toMat(float m[16], const float q[4])
{
  float Nq = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
  float s = 2/Nq;
  float wx, wy, wz, xx, yy, yz, xy, xz, zz, xw, yw, zw;

  wx = q[3]*q[0]*s;
  wy = q[3]*q[1]*s;
  wz = q[3]*q[2]*s;
  xx = q[0]*q[0]*s;
  xy = q[0]*q[1]*s;
  xz = q[0]*q[2]*s;
  yy = q[1]*q[1]*s;
  yz = q[1]*q[2]*s;
  zz = q[2]*q[2]*s;

  m[0] = 1-(yy+zz); m[1] = xy+wz; m[2] = xz-wy; m[3] = 0;
  m[4] = xy-wz; m[5] = 1-(xx+zz); m[6] = yz+wx; m[7] = 0;
  m[8] = xz+wy; m[9] = yz-wx; m[10] = 1-(xx+yy); m[11] = 0;
  m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}
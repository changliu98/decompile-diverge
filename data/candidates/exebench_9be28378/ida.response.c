void __cdecl mat3d_rotateQuatVec_new(double *matrix, const double *quat)
{
  double zz; // [rsp+0h] [rbp-88h]
  double yz; // [rsp+8h] [rbp-80h]
  double yy; // [rsp+10h] [rbp-78h]
  double xz; // [rsp+18h] [rbp-70h]
  double xy; // [rsp+20h] [rbp-68h]
  double xx; // [rsp+28h] [rbp-60h]
  double wz; // [rsp+30h] [rbp-58h]
  double wy; // [rsp+38h] [rbp-50h]
  double wx; // [rsp+40h] [rbp-48h]
  double zs; // [rsp+48h] [rbp-40h]
  double ys; // [rsp+50h] [rbp-38h]
  double xs; // [rsp+58h] [rbp-30h]
  double s; // [rsp+60h] [rbp-28h]

  s = 2.0 / (quat[3] * quat[3] + quat[2] * quat[2] + *quat * *quat + quat[1] * quat[1]);
  xs = *quat * s;
  ys = quat[1] * s;
  zs = quat[2] * s;
  wx = quat[3] * xs;
  wy = quat[3] * ys;
  wz = quat[3] * zs;
  xx = *quat * xs;
  xy = *quat * ys;
  xz = *quat * zs;
  yy = quat[1] * ys;
  yz = quat[1] * zs;
  zz = quat[2] * zs;
  *matrix = 1.0 - (yy + zz);
  matrix[3] = xy - wz;
  matrix[6] = xz + wy;
  matrix[1] = xy + wz;
  matrix[4] = 1.0 - (xx + zz);
  matrix[7] = yz - wx;
  matrix[2] = xz - wy;
  matrix[5] = yz + wx;
  matrix[8] = 1.0 - (xx + yy);
}
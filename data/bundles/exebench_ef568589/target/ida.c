void __cdecl mat3f_rotateQuatVec_new(float *matrix, const float *quat)
{
  float v2; // xmm0_4
  float v3; // xmm0_4
  float v4; // xmm0_4
  float v5; // xmm0_4
  float zz; // [rsp+0h] [rbp-54h]
  float yz; // [rsp+4h] [rbp-50h]
  float yy; // [rsp+8h] [rbp-4Ch]
  float xz; // [rsp+Ch] [rbp-48h]
  float xy; // [rsp+10h] [rbp-44h]
  float xx; // [rsp+14h] [rbp-40h]
  float wz; // [rsp+18h] [rbp-3Ch]
  float wy; // [rsp+1Ch] [rbp-38h]
  float wx; // [rsp+20h] [rbp-34h]
  float zs; // [rsp+24h] [rbp-30h]
  float ys; // [rsp+28h] [rbp-2Ch]
  float xs; // [rsp+2Ch] [rbp-28h]

  v2 = 2.0
     / (float)((float)(quat[3] * quat[3])
             + (float)((float)(quat[2] * quat[2]) + (float)((float)(*quat * *quat) + (float)(quat[1] * quat[1]))));
  xs = *quat * v2;
  ys = quat[1] * v2;
  zs = quat[2] * v2;
  wx = quat[3] * xs;
  wy = quat[3] * ys;
  wz = quat[3] * zs;
  xx = *quat * xs;
  xy = *quat * ys;
  xz = *quat * zs;
  yy = quat[1] * ys;
  yz = quat[1] * zs;
  zz = quat[2] * zs;
  v3 = 1.0 - (float)(yy + zz);
  *matrix = v3;
  matrix[3] = xy - wz;
  matrix[6] = xz + wy;
  matrix[1] = xy + wz;
  v4 = 1.0 - (float)(xx + zz);
  matrix[4] = v4;
  matrix[7] = yz - wx;
  matrix[2] = xz - wy;
  matrix[5] = yz + wx;
  v5 = 1.0 - (float)(xx + yy);
  matrix[8] = v5;
}
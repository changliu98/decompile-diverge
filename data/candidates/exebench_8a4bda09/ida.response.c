void __cdecl rsQuat_toMat(float *q, float *mat)
{
  float zz; // [rsp+0h] [rbp-44h]
  float yz; // [rsp+4h] [rbp-40h]
  float yy; // [rsp+8h] [rbp-3Ch]
  float xz; // [rsp+Ch] [rbp-38h]
  float xy; // [rsp+10h] [rbp-34h]
  float xx; // [rsp+14h] [rbp-30h]
  float wz; // [rsp+18h] [rbp-2Ch]
  float wy; // [rsp+1Ch] [rbp-28h]
  float wx; // [rsp+20h] [rbp-24h]
  float zs; // [rsp+24h] [rbp-20h]
  float ys; // [rsp+28h] [rbp-1Ch]
  float xs; // [rsp+2Ch] [rbp-18h]
  float s; // [rsp+30h] [rbp-14h]

  if ( *q == 0.0 && q[1] == 0.0 && q[2] == 0.0 )
  {
    *mat = 1.0;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;
    mat[4] = 0.0;
    mat[5] = 1.0;
    mat[6] = 0.0;
    mat[7] = 0.0;
    mat[8] = 0.0;
    mat[9] = 0.0;
    mat[10] = 1.0;
    mat[11] = 0.0;
    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 0.0;
    mat[15] = 1.0;
  }
  else
  {
    s = 2.0
      / (float)((float)(q[3] * q[3]) + (float)((float)(q[2] * q[2]) + (float)((float)(*q * *q) + (float)(q[1] * q[1]))));
    xs = *q * s;
    ys = q[1] * s;
    zs = q[2] * s;
    wx = q[3] * xs;
    wy = q[3] * ys;
    wz = q[3] * zs;
    xx = *q * xs;
    xy = *q * ys;
    xz = *q * zs;
    yy = q[1] * ys;
    yz = q[1] * zs;
    zz = q[2] * zs;
    *mat = (float)(1.0 - yy) - zz;
    mat[1] = xy + wz;
    mat[2] = xz - wy;
    mat[3] = 0.0;
    mat[4] = xy - wz;
    mat[5] = (float)(1.0 - xx) - zz;
    mat[6] = yz + wx;
    mat[7] = 0.0;
    mat[8] = xz + wy;
    mat[9] = yz - wx;
    mat[10] = (float)(1.0 - xx) - yy;
    mat[11] = 0.0;
    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 0.0;
    mat[15] = 1.0;
  }
}
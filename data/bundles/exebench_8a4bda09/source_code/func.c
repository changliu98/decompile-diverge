
void rsQuat_toMat (float *q, float *mat)
{
 float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;




 if (q[0] == 0.0f && q[1] == 0.0f && q[2] == 0.0f) {
  mat[0] = 1.0f;
  mat[1] = 0.0f;
  mat[2] = 0.0f;
  mat[3] = 0.0f;
  mat[4] = 0.0f;
  mat[5] = 1.0f;
  mat[6] = 0.0f;
  mat[7] = 0.0f;
  mat[8] = 0.0f;
  mat[9] = 0.0f;
  mat[10] = 1.0f;
  mat[11] = 0.0f;
  mat[12] = 0.0f;
  mat[13] = 0.0f;
  mat[14] = 0.0f;
  mat[15] = 1.0f;
  return;
 }

 s = 2.0f / (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
 xs = q[0] * s;
 ys = q[1] * s;
 zs = q[2] * s;
 wx = q[3] * xs;
 wy = q[3] * ys;
 wz = q[3] * zs;
 xx = q[0] * xs;
 xy = q[0] * ys;
 xz = q[0] * zs;
 yy = q[1] * ys;
 yz = q[1] * zs;
 zz = q[2] * zs;

 mat[0] = 1.0f - yy - zz;
 mat[1] = xy + wz;
 mat[2] = xz - wy;
 mat[3] = 0.0f;
 mat[4] = xy - wz;
 mat[5] = 1.0f - xx - zz;
 mat[6] = yz + wx;
 mat[7] = 0.0f;
 mat[8] = xz + wy;
 mat[9] = yz - wx;
 mat[10] = 1.0f - xx - yy;
 mat[11] = 0.0f;
 mat[12] = 0.0f;
 mat[13] = 0.0f;
 mat[14] = 0.0f;
 mat[15] = 1.0f;
}

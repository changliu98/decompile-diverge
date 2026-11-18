void qmat(float q[4], float m[16])
{
  float s; float xs; float ys; float zs;
  float wx; float wy; float wz;
  float xx; float yy; float zz;
  float xy; float xz; float yz;
  if (q[0] == 0 && q[1] == 0 && q[2] == 0) {
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;
    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
  } else {
    s = 2 / (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    xs = s * q[0];
    ys = s * q[1];
    zs = s * q[2];
    wx = q[3] * xs;
    wy = q[3] * ys;
    wz = q[3] * zs;
    xx = q[0] * xs;
    xy = q[0] * ys;
    xz = q[0] * zs;
    yy = q[1] * ys;
    yz = q[1] * zs;
    zz = q[2] * zs;
    m[0] = 1 - yy - zz;
    m[1] = xy + wz;
    m[2] = xz - wy;
    m[3] = 0;
    m[4] = xy - wz;
    m[5] = 1 - xx - zz;
    m[6] = yz + wx;
    m[7] = 0;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = 1 - xx - yy;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
  }
}
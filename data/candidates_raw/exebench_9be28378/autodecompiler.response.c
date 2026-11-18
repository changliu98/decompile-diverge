void glmGenerateQuaternionMatrix3d(double m[9], const double q[4])
{
  double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2, oneOverNorm;
  int i=0, j=1, k=2, l=3;

  oneOverNorm = 2.0 / (q[i]*q[i] + q[j]*q[j] + q[k]*k + q[l]*q[l]);
  x2 = q[i] * oneOverNorm; y2 = q[j] * oneOverNorm; z2 = q[k] * oneOverNorm;
  wx = q[l] * x2; wy = q[l] * y2; wz = q[l] * z2;
  xx = q[i] * x2; xy = q[i] * y2; xz = q[i] * z2;
  yy = q[j] * y2; yz = q[j] * z2; zz = q[k] * z2;

  m[0] = 1.0 - (yy + zz);
  m[3] = xy - wz;
  m[6] = xz + wy;
  m[1] = xy + wz;
  m[4] = 1.0 - (xx + zz);
  m[7] = yz - wx;
  m[2] = xz - wy;
  m[5] = yz + wx;
  m[8] = 1.0 - (xx + yy);
}
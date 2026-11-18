void glmCrossProduct3d(double result[3], const double v1[3], const double v2[3])
{
  result[0]=((v1[1] * v2[2]) ^ ((long long)(1) << 63)) + ((unsigned long long)v1[2] * v2[0]);
  result[1]=(((v1[0] * v2[2]) ^ ((long long)(1) << 63)) ^ ((long long)(1) << 63)) + ((unsigned long long)v1[2] * v2[1]);
  result[2]=((v1[0] * v2[1]) ^ ((long long)(1) << 63)) + ((unsigned long long)v1[1] * v2[0]);
}
void __cdecl mtxMultiply(float *ret, const float *lhs, const float *rhs)
{
  *ret = (float)(lhs[12] * rhs[3])
       + (float)((float)(lhs[8] * rhs[2]) + (float)((float)(*lhs * *rhs) + (float)(lhs[4] * rhs[1])));
  ret[1] = (float)(lhs[13] * rhs[3])
         + (float)((float)(lhs[9] * rhs[2]) + (float)((float)(lhs[1] * *rhs) + (float)(lhs[5] * rhs[1])));
  ret[2] = (float)(lhs[14] * rhs[3])
         + (float)((float)(lhs[10] * rhs[2]) + (float)((float)(lhs[2] * *rhs) + (float)(lhs[6] * rhs[1])));
  ret[3] = (float)(lhs[15] * rhs[3])
         + (float)((float)(lhs[11] * rhs[2]) + (float)((float)(lhs[3] * *rhs) + (float)(lhs[7] * rhs[1])));
  ret[4] = (float)(lhs[12] * rhs[7])
         + (float)((float)(lhs[8] * rhs[6]) + (float)((float)(*lhs * rhs[4]) + (float)(lhs[4] * rhs[5])));
  ret[5] = (float)(lhs[13] * rhs[7])
         + (float)((float)(lhs[9] * rhs[6]) + (float)((float)(lhs[1] * rhs[4]) + (float)(lhs[5] * rhs[5])));
  ret[6] = (float)(lhs[14] * rhs[7])
         + (float)((float)(lhs[10] * rhs[6]) + (float)((float)(lhs[2] * rhs[4]) + (float)(lhs[6] * rhs[5])));
  ret[7] = (float)(lhs[15] * rhs[7])
         + (float)((float)(lhs[11] * rhs[6]) + (float)((float)(lhs[3] * rhs[4]) + (float)(lhs[7] * rhs[5])));
  ret[8] = (float)(lhs[12] * rhs[11])
         + (float)((float)(lhs[8] * rhs[10]) + (float)((float)(*lhs * rhs[8]) + (float)(lhs[4] * rhs[9])));
  ret[9] = (float)(lhs[13] * rhs[11])
         + (float)((float)(lhs[9] * rhs[10]) + (float)((float)(lhs[1] * rhs[8]) + (float)(lhs[5] * rhs[9])));
  ret[10] = (float)(lhs[14] * rhs[11])
          + (float)((float)(lhs[10] * rhs[10]) + (float)((float)(lhs[2] * rhs[8]) + (float)(lhs[6] * rhs[9])));
  ret[11] = (float)(lhs[15] * rhs[11])
          + (float)((float)(lhs[11] * rhs[10]) + (float)((float)(lhs[3] * rhs[8]) + (float)(lhs[7] * rhs[9])));
  ret[12] = (float)(lhs[12] * rhs[15])
          + (float)((float)(lhs[8] * rhs[14]) + (float)((float)(*lhs * rhs[12]) + (float)(lhs[4] * rhs[13])));
  ret[13] = (float)(lhs[13] * rhs[15])
          + (float)((float)(lhs[9] * rhs[14]) + (float)((float)(lhs[1] * rhs[12]) + (float)(lhs[5] * rhs[13])));
  ret[14] = (float)(lhs[14] * rhs[15])
          + (float)((float)(lhs[10] * rhs[14]) + (float)((float)(lhs[2] * rhs[12]) + (float)(lhs[6] * rhs[13])));
  ret[15] = (float)(lhs[15] * rhs[15])
          + (float)((float)(lhs[11] * rhs[14]) + (float)((float)(lhs[3] * rhs[12]) + (float)(lhs[7] * rhs[13])));
}
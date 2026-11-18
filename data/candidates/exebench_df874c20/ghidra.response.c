void mtxMultiply(float *ret,float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  float *ret_local;
  
  *ret = lhs[0xc] * rhs[3] + lhs[8] * rhs[2] + *lhs * *rhs + lhs[4] * rhs[1];
  ret[1] = lhs[0xd] * rhs[3] + lhs[9] * rhs[2] + lhs[1] * *rhs + lhs[5] * rhs[1];
  ret[2] = lhs[0xe] * rhs[3] + lhs[10] * rhs[2] + lhs[2] * *rhs + lhs[6] * rhs[1];
  ret[3] = lhs[0xf] * rhs[3] + lhs[0xb] * rhs[2] + lhs[3] * *rhs + lhs[7] * rhs[1];
  ret[4] = lhs[0xc] * rhs[7] + lhs[8] * rhs[6] + *lhs * rhs[4] + lhs[4] * rhs[5];
  ret[5] = lhs[0xd] * rhs[7] + lhs[9] * rhs[6] + lhs[1] * rhs[4] + lhs[5] * rhs[5];
  ret[6] = lhs[0xe] * rhs[7] + lhs[10] * rhs[6] + lhs[2] * rhs[4] + lhs[6] * rhs[5];
  ret[7] = lhs[0xf] * rhs[7] + lhs[0xb] * rhs[6] + lhs[3] * rhs[4] + lhs[7] * rhs[5];
  ret[8] = lhs[0xc] * rhs[0xb] + lhs[8] * rhs[10] + *lhs * rhs[8] + lhs[4] * rhs[9];
  ret[9] = lhs[0xd] * rhs[0xb] + lhs[9] * rhs[10] + lhs[1] * rhs[8] + lhs[5] * rhs[9];
  ret[10] = lhs[0xe] * rhs[0xb] + lhs[10] * rhs[10] + lhs[2] * rhs[8] + lhs[6] * rhs[9];
  ret[0xb] = lhs[0xf] * rhs[0xb] + lhs[0xb] * rhs[10] + lhs[3] * rhs[8] + lhs[7] * rhs[9];
  ret[0xc] = lhs[0xc] * rhs[0xf] + lhs[8] * rhs[0xe] + *lhs * rhs[0xc] + lhs[4] * rhs[0xd];
  ret[0xd] = lhs[0xd] * rhs[0xf] + lhs[9] * rhs[0xe] + lhs[1] * rhs[0xc] + lhs[5] * rhs[0xd];
  ret[0xe] = lhs[0xe] * rhs[0xf] + lhs[10] * rhs[0xe] + lhs[2] * rhs[0xc] + lhs[6] * rhs[0xd];
  ret[0xf] = lhs[0xf] * rhs[0xf] + lhs[0xb] * rhs[0xe] + lhs[3] * rhs[0xc] + lhs[7] * rhs[0xd];
  return;
}
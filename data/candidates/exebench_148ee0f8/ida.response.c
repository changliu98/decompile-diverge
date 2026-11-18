void __cdecl InvMat22(float *invA, float *A)
{
  __m128i v2; // xmm1
  float detA; // [rsp+0h] [rbp-14h]

  v2 = (__m128i)*((unsigned int *)A + 1);
  *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * A[2];
  detA = (float)(*A * A[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  *invA = (float)(1.0 / detA) * A[3];
  invA[1] = (float)(-1.0 / detA) * A[1];
  invA[2] = (float)(-1.0 / detA) * A[2];
  invA[3] = (float)(1.0 / detA) * *A;
}
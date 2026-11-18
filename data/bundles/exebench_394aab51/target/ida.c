void __cdecl rsQuat_postMult(float *q, float *preQuat)
{
  __m128i v2; // xmm1
  float tempw; // [rsp+0h] [rbp-20h]
  float tempz; // [rsp+4h] [rbp-1Ch]
  float tempy; // [rsp+8h] [rbp-18h]
  float tempx; // [rsp+Ch] [rbp-14h]

  tempx = *q;
  tempy = q[1];
  tempz = q[2];
  tempw = q[3];
  *q = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(tempy)) ^ 0x80000000) * preQuat[2])
     + (float)((float)(preQuat[1] * tempz) + (float)((float)(preQuat[3] * *q) + (float)(tempw * *preQuat)));
  q[1] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(tempz)) ^ 0x80000000) * *preQuat)
       + (float)((float)(preQuat[2] * tempx) + (float)((float)(preQuat[3] * tempy) + (float)(tempw * preQuat[1])));
  q[2] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(tempx)) ^ 0x80000000) * preQuat[1])
       + (float)((float)(*preQuat * tempy) + (float)((float)(preQuat[3] * tempz) + (float)(tempw * preQuat[2])));
  v2 = (__m128i)*(unsigned int *)preQuat;
  *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * tempx;
  q[3] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)preQuat + 2)) ^ 0x80000000) * tempz)
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)preQuat + 1)) ^ 0x80000000) * tempy)
               + (float)((float)(preQuat[3] * tempw) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000)));
}
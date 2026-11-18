void __cdecl rsQuat_preMult(float *q, float *postQuat)
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
  *q = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)postQuat + 1)) ^ 0x80000000) * tempz)
     + (float)((float)(tempy * postQuat[2]) + (float)((float)(tempw * *postQuat) + (float)(postQuat[3] * *q)));
  q[1] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)postQuat + 2)) ^ 0x80000000) * tempx)
       + (float)((float)(tempz * *postQuat) + (float)((float)(tempw * postQuat[1]) + (float)(postQuat[3] * tempy)));
  q[2] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)postQuat) ^ 0x80000000) * tempy)
       + (float)((float)(tempx * postQuat[1]) + (float)((float)(tempw * postQuat[2]) + (float)(postQuat[3] * tempz)));
  v2 = (__m128i)LODWORD(tempx);
  *(float *)v2.m128i_i32 = tempx * *postQuat;
  q[3] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(tempz)) ^ 0x80000000) * postQuat[2])
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(tempy)) ^ 0x80000000) * postQuat[1])
               + (float)((float)(tempw * postQuat[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000)));
}
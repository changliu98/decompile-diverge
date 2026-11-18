void __cdecl pa(float *e, float t, float t2)
{
  long j; // [rsp+0h] [rbp-18h]

  for ( j = 0LL; j < 6; ++j )
  {
    *e = (float)((float)((float)(*e + e[1]) + e[2]) - e[3]) * t;
    e[1] = (float)((float)((float)(*e + e[1]) - e[2]) + e[3]) * t;
    e[2] = (float)((float)((float)(*e - e[1]) + e[2]) + e[3]) * t;
    e[3] = (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)e) ^ 0x80000000) + e[1])
                         + e[2])
                 + e[3])
         / t2;
  }
}
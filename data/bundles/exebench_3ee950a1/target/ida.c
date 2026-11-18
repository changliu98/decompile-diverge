float __cdecl hpluck(float xin, float *q)
{
  float v2; // xmm0_4
  float v3; // xmm0_4
  int ip_0; // [rsp+0h] [rbp-18h]
  float temp; // [rsp+4h] [rbp-14h]

  *q = *q + 1.0;
  if ( q[1] < *q )
  {
    ip_0 = 20;
    *q = 20.0;
  }
  else
  {
    ip_0 = (int)*q;
  }
  v2 = (1.0 - q[8]) * q[ip_0] + (float)(q[8] * q[7]);
  q[7] = v2;
  temp = q[9] * (float)((float)(q[2] * q[ip_0]) + (float)(q[3] * q[6]));
  q[6] = q[ip_0];
  q[ip_0] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 10)) ^ 0x80000000) * q[5])
          + (float)((float)(q[10] * temp) + q[4]);
  v3 = xin + q[ip_0];
  q[ip_0] = v3;
  q[5] = v3;
  q[4] = temp;
  return q[7];
}
float __cdecl pluck(float sig, float *q)
{
  float v2; // xmm1_4
  float v3; // xmm2_4
  int ip_0; // [rsp+4h] [rbp-18h]
  float temp; // [rsp+8h] [rbp-14h]

  *q = *q + 1.0;
  if ( q[1] <= *q )
  {
    ip_0 = 4;
    *q = 4.0;
    temp = q[4];
    v2 = (float)(q[2] * temp) + sig;
    v3 = q[(int)(q[1] - 1.0)];
  }
  else
  {
    ip_0 = (int)*q;
    temp = q[ip_0];
    v2 = (float)(q[2] * temp) + sig;
    v3 = q[ip_0 - 1];
  }
  q[ip_0] = (float)(q[3] * v3) + v2;
  return temp;
}
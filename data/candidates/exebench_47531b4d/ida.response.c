void __cdecl normalize_quat(float *q)
{
  float mag; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  mag = (float)(q[3] * q[3]) + (float)((float)(q[2] * q[2]) + (float)((float)(*q * *q) + (float)(q[1] * q[1])));
  for ( i = 0; i < 4; ++i )
    q[i] = q[i] / mag;
}
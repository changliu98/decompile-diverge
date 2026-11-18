void __cdecl normalize_quat(float *q)
{
  float mag_sq;
  int i;

  mag_sq = (q[0] * q[0]) + (q[1] * q[1]) + (q[2] * q[2]) + (q[3] * q[3]);
  
  for (i = 0; i < 4; ++i)
    q[i] = q[i] / mag_sq;
}
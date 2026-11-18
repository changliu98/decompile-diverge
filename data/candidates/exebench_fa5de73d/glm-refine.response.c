void __cdecl QuaternionMult(float *pfQOut, float *pfQIn1, float *pfQIn2)
{
  float q1x = pfQIn1[0];
  float q1y = pfQIn1[1];
  float q1z = pfQIn1[2];
  float q1w = pfQIn1[3];

  float q2x = pfQIn2[0];
  float q2y = pfQIn2[1];
  float q2z = pfQIn2[2];
  float q2w = pfQIn2[3];

  pfQOut[0] = (q1w * q2x) + (q1x * q2w) + (q1y * q2z) - (q1z * q2y);
  pfQOut[1] = (q1w * q2y) - (q1x * q2z) + (q1y * q2w) + (q1z * q2x);
  pfQOut[2] = (q1w * q2z) + (q1x * q2y) - (q1y * q2x) + (q1z * q2w);
  pfQOut[3] = (q1w * q2w) - (q1x * q2x) - (q1y * q2y) - (q1z * q2z);
}
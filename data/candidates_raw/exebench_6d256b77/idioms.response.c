float get_inter(float *S, int i1, int i2, int N)
{
  int i;
  float inter = 0.0;
  float interS1 = 0.0;
  float interS2 = 0.0;
  for (i = 0; i < N; i++) {
    if (S[i + i1 * N] == 1 && S[i + i2 * N] == 1)
      inter = inter + 1.0;
    if (S[i + i1 * N] == 1)
      interS1 = interS1 + 1.0;
    if (S[i + i2 * N] == 1)
      interS2 = interS2 + 1.0;
  }
  if (interS1 < interS2)
    return (inter / interS1);
  else
    return (inter / interS2);
}
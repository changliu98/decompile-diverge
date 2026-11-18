void dot4(float v1[4], float v2[4], float results[4])
{
  int i;
  for (i = 0; i < 4; i++)
    results[i] = 0.0f;
  for (i = 0; i < 4; i++)
  {
    results[0] += v1[i] * v2[i];
    results[1] += v1[i + 4] * v2[i + 4];
    results[2] += v1[i + 8] * v2[i + 8];
    results[3] += v1[i + 12] * v2[i + 12];
  }
}
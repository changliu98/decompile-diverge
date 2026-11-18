static float calc_sigma(float *bufx, float *bufy, unsigned long cnt)
{
  float sigma = 0.0f;
  unsigned long i;
  for (i = 0; i < cnt; i++)
    sigma += (bufx[i] * bufy[i]) * bufx[i];
  cnt = (cnt & 1) + (cnt >> 1);
  sigma /= (float)cnt;
  return (sigma);
}
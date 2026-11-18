void max(float *max, float *v)
{
  int i;
  for (i = 0; i < 3; i++)
    if (v[i] > max[i])
      max[i] = v[i];
}
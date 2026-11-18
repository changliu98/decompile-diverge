int is_all_zero(float *spectrum, int N)
{
  int i;
  for (i = 0; i <= N; i++)
    if (spectrum[i] > 1.1754943508e-38F)
      return 0;
  return 1;
}
int get_max(float *in)
{
  float en = 0;
  int max = -1;
  int i = 0;
  for (i = 0; i < 16; i++)
  {
    if (in[i] > en)
    {
      en = in[i];
      max = i;
    }
  }
  if (max < 0)
  {
    return -1;
  }
  for (i = 0; i < 16; i++)
  {
    if (max != i)
    {
      if (in[i] > (en * 0.1))
      {
        return -1;
      }
    }
  }
  return max;
}
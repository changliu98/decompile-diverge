static unsigned int get_key(float *val, float thres)
{
  unsigned int i;
  unsigned int key = 0;
  for (i = 0; i < 8; i++)
    if (val[i] > thres)
      key |= (1 << i);
  return key;
}
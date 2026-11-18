static unsigned short spds_getmax(unsigned short *spds, int num, unsigned short dflt)
{
  unsigned short max = 0;
  int i;
  for (i = 0; i < num; i++)
    if (spds[i] > max)
      max = spds[i];
  if (max == 0)
    return dflt;
  return max;
}
void update16(unsigned short *target, int max, int intensity, int limit)
{
  if (*target > max)
    *target = limit;
  else
    *target += intensity;
}
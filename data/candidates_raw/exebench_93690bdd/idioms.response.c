void limit(int *val, int min, int max)
{
  if (*val > max)
    *val = max;
  else if (*val < min)
    *val = min;
}
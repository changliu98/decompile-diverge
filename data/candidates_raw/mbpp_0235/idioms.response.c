int set_bit(int n)
{
  int i = 0;
  int res = 0;
  int temp = n;
  while (temp > 0)
  {
    if (i % 2 == 1)
    {
      res |= (1 << i);
    }
    i++;
    temp = temp >> 1;
  }
  res = res | n;
  return res;
}
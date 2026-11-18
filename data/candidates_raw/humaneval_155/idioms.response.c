void count_even_odd(int num, int count[2])
{
  int numa = abs(num);
  int even = 0;
  int odd = 0;
  do
  {
    int digit = numa % 10;
    if (digit % 2 == 0)
    {
      even++;
    }
    else
    {
      odd++;
    }
    numa = numa / 10;
  }
  while (numa > 0);
  count[0] = even;
  count[1] = odd;
}
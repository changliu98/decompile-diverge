int is_valid(int n)
{
  int i;
  int temp;
  int count;
  for (i = 0; i < 10; i++)
  {
    temp = n;
    count = 0;
    while (temp > 0)
    {
      if (temp % 10 == i)
      {
        count++;
      }
      if (count > i)
      {
        return 0;
      }
      temp /= 10;
    }
  }
  return 1;
}
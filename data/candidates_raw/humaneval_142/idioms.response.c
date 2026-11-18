int f1(int *lst, int size)
{
  int sum = 0;
  int i;
  for (i = 0; i < size; i++)
  {
    if (i % 3 == 0)
    {
      sum += lst[i] * lst[i];
    }
    else if (i % 4 == 0)
    {
      sum += lst[i] * lst[i] * lst[i];
    }
    else
    {
      sum += lst[i];
    }
  }
  return (sum);
}
int get_sum_of_odd(int *list, int size)
{
  int sum = 0;
  int i;
  for (i = 0; i * 2 < size; i++)
  {
    if (list[i * 2] % 2 == 1)
    {
      sum += list[i * 2];
    }
  }
  return (sum);
}
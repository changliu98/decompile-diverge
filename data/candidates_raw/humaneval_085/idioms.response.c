int sum_of_even(int *list, int size)
{
  int sum = 0;
  int i = 0;
  for (i = 0; i * 2 + 1 < size; i++)
  {
    if (list[i * 2 + 1] % 2 == 0)
    {
      sum += list[i * 2 + 1];
    }
  }
  return sum;
}
int func0(int *array, int n)
{
  int sum = 0;
  int i = 0;
  int j = 0;
  int count = 1;
  for (i = 0; i < n; i++)
  {
    count = 1;
    for (j = 0; j < n; j++)
    {
      if (array[j] == array[i] && j != i)
      {
        count++;
      }
    }
    if (count > 1)
    {
      sum += array[i];
    }
  }
  return (sum);
}
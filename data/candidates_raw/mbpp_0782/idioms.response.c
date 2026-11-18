int sum(int *array, int length)
{
  int sum = 0;
  int i = 0;
  for (i = 0; i < length; i++)
  {
    sum += array[i] * ((1 + (length - i) * (i + 1)) / 2);
  }
  return sum;
}
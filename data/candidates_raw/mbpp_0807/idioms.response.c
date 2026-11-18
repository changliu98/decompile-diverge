int get_first_odd(int *array, int length)
{
  int i;
  for (i = 0; i < length; i++)
    if (array[i] % 2 == 1)
      return array[i];
  return -1;
}
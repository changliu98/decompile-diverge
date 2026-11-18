double average(int *numbers, int size)
{
  int total = 0;
  int i;
  for (i = 0; i < size; i++)
    total += numbers[i];
  return (double) total / (double) size;
}
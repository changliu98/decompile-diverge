double func0(int *numbers, int size)
{
  int i;
  double total = 1.0;
  for (i = 0; i < size; i++)
    total *= numbers[i];
  return total / size;
}
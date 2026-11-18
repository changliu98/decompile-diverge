int func0(int *list, int size)
{
  int total = 0;
  int i;
  for (i = 0; i < size; i++)
    total += list[i];
  return total;
}
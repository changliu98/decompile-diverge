int func0(int *list, int list_size)
{
  int count = 0;
  int i;
  for (i = 0; i < list_size; i++)
    if (list[i] >= 0)
      count++;
  return count;
}
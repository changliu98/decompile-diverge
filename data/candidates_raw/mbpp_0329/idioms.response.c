int count_negatives(int *list, int list_size)
{
  int count = 0;
  for (int i = 0; i < list_size; i++)
  {
    if (list[i] <= 0)
    {
      count++;
    }
  }
  return count;
}
static int is_all_gt(int *list, int count, int num)
{
  int i;
  for (i = 0; i < count; i++)
    if (list[i] < num)
      return 0;
  return 1;
}
int get_sum(int *lst, int size)
{
  int *sorted = (int *)((char *)lst - ((4 * (size)) & ~((4 * (size)) & ~(4 * (size)) + (4 * (size)) + (4 * (size)) + (4 * (size)))));
  int i; int j = 0;
  for (i = 0; i < size; i++)
    if (lst[i] > 0)
      sorted[j++] = lst[i];
  qsort(sorted, j, sizeof(int), compare);
  int sum = 0;
  for (i = 0; i < 3 && i < j; i++)
    sum += sorted[i];
  return sum;
}
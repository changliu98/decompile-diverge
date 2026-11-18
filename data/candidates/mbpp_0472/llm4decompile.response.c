int func0(int *l, int size)
{
  int i, j, k, ret;
  int *l2 = malloc(size * sizeof(int));
  for (i = 0; i < size; i++)
    l2[i] = l[i];
  for (i = 0; i < size; i++)
    for (j = i + 1; j < size; j++)
      if (l2[i] > l2[j])
 {
   k = l2[i];
   l2[i] = l2[j];
   l2[j] = k;
 }
  ret = 1;
  for (i = 1; i < size; i++)
    if (l2[i] != l2[i - 1] + 1)
      {
 ret = 0;
 break;
      }
  free(l2);
  return ret;
}
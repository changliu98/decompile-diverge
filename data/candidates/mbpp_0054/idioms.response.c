void func0(int *list, int n)
{
  int i;
  int max_value = 0;
  for (i = 0; i < n; i++)
  {
    if (list[i] > max_value)
      max_value = list[i];
  }
  int *count = (int *)malloc((max_value + 1) * sizeof(int));
  for (i = 0; i <= max_value; i++)
    count[i] = 0;
  for (i = 0; i < n; i++)
    count[list[i]]++;
  int j = 0;
  for (i = 0; i <= max_value; i++)
  {
    int k;
    for (k = 0; k < count[i]; k++)
    {
      list[j] = i;
      j++;
    }
  }
  free(count);
}
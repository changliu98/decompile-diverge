int func0(int *arr, int n)
{
  int i;
  int found = 0;
  for (i = 0; i < n; i++)
    if (arr[i] == 1)
    {
      found = 1;
      break;
    }
  if (!found)
    return 1;
  for (i = 0; i < n; i++)
    if (arr[i] < 1 || arr[i] > n)
      arr[i] = 1;
  for (i = 0; i < n; i++)
    arr[(arr[i] - 1) % n] += n;
  for (i = 0; i < n; i++)
    if (arr[i] <= n)
      return i + 1;
  return n + 1;
}
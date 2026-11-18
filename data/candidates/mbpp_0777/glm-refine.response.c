int __cdecl sum_unique(int *arr, int n)
{
  int sum;
  int i;

  qsort(arr, n, sizeof(int), compare);
  
  sum = arr[0];
  for (i = 0; i < n - 1; ++i)
  {
    if (arr[i] != arr[i + 1])
      sum += arr[i + 1];
  }
  
  return sum;
}
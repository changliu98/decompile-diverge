int next_combination(int *arr, int len, int maxval)
{
  int i;
  for (i = 0; i < len; i++) {
    arr[i]++;
    if (arr[i] <= maxval)
      return 1;
    arr[i] = 0;
  }
  return 0;
}
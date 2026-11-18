int func0(int *arr, int k)
{
  int i;
  int sum = 0;
  for (i = 0; i < k; i++)
    if (arr[i] >= -100 && arr[i] <= 100)
      sum += arr[i];
  return sum;
}
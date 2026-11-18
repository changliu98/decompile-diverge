int func0(int *arr, int n)
{
  int *end = arr + n;
  int *sum = (int *)((int *)end - ((int *)end - (int *)arr - 1));
  int i;
  int max1; int max2; int max3;
  int sum1; int sum2;
  if (n > 0)
    sum[0] = *arr;
  if (n > 1)
    sum[1] = arr[1] + *arr;
  if (n > 2) {
    if (sum[1] > (arr[1] + arr[2]))
      sum2 = sum[1];
    else
      sum2 = arr[1] + arr[2];
    if (sum2 > (arr[2] + *arr))
      sum1 = sum2;
    else
      sum1 = arr[2] + *arr;
    sum[2] = sum1;
  }
  for (i = 3; i < n; i++) {
    max1 = sum[i - 1];
    max2 = arr[i] + sum[i - 2];
    max3 = arr[i - 1] + arr[i] + sum[i - 3];
    if (max1 > max2)
      sum1 = max1;
    else
      sum1 = max2;
    if (sum1 > max3)
      sum2 = sum1;
    else
      sum2 = max3;
    sum[i] = sum2;
  }
  return (sum[n - 1]);
}
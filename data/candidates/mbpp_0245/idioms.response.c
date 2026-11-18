int func0(int *array, int n)
{
  int *left = array;
  int *right = array + n;
  int *left_sum = (int *) (left - ( ( (sizeof(int) * n) + (sizeof(int) * 1) - 1 ) & ~( (sizeof(int) * n) + (sizeof(int) * 1) - 1 ) ));
  int *right_sum = (int *) (right - ( ( (sizeof(int) * n) + (sizeof(int) * 1) - 1 ) & ~( (sizeof(int) * n) + (sizeof(int) * 1) - 1 ) ));
  int i; int j;
  for (i = 0; i < n; i++)
    left_sum[i] = right_sum[i] = left[i];
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++)
      if (left[i] > left[j] && left_sum[i] < left[i] + left_sum[j])
        left_sum[i] = left[i] + left_sum[j];
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++)
      if (right[n - i - 1] > right[n - j - 1] && right_sum[n - i - 1] < right[n - i - 1] + right_sum[n - j - 1])
        right_sum[n - i - 1] = right[n - i - 1] + right_sum[n - j - 1];
  int max_sum = -99999999;
  for (i = 0; i < n; i++)
    if (max_sum < left_sum[i] + right_sum[i] - left[i])
      max_sum = left_sum[i] + right_sum[i] - left[i];
  return max_sum;
}
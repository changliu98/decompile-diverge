int _max_sum(int *arr, int len) {
  int i;
  int sum[len];
  if (len >= 1) sum[0] = arr[0];
  if (len >= 2) sum[1] = arr[0] + arr[1];
  if (len >= 3) sum[2] = (sum[1] > arr[1] + arr[2] ? sum[1] : arr[1] + arr[2]);
  for (i = 3; i < len; i++)
    sum[i] = (((sum[i - 1]) > (sum[i - 2] + arr[i])) ? (sum[i - 1])
                                                     : (sum[i - 2] + arr[i]));
  return sum[len - 1];
}
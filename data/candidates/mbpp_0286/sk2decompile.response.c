int _max_subarray(int *array, int len, int n) {
  int max = 0x80000000;
  int sum = 0;
  int i;
  for (i = 0; i < len * n; i++) {
    sum += array[i % len];
    if (sum > max) max = sum;
    if (sum < 0) sum = 0;
  }
  return max;
}
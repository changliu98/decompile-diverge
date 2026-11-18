int _max_subarray(int *array, int size) {
  int max_sum = 0x80000000;
  int sum = 0;
  int max_start = 0;
  int max_end = 0;
  int i;
  for (i = 0; i < size; i++) {
    sum += array[i];
    if (max_sum < sum) {
      max_sum = sum;
      max_start = i;
    }
    if (sum < 0) {
      sum = 0;
      max_end = i + 1;
    }
  }
  return max_start - max_end + 1;
}
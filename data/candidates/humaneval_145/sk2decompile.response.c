int* func0(int* nums, int numsSize) {
  int* nums_ptr = nums;
  int nums_size = numsSize;
  int* nums_sum = malloc(nums_size * sizeof(int));
  char num_str[12];
  int i, j, sum, len;
  for (i = 0; i < nums_size; i++) {
    sprintf(num_str, "%d", abs(nums_ptr[i]));
    sum = 0;
    len = strlen(num_str);
    for (j = 1; j < len; j++) {
      sum += num_str[j] - '0';
    }
    if (nums_ptr[i] > 0) {
      sum += num_str[0] - '0';
    } else {
      sum -= num_str[0] - '0';
    }
    nums_sum[i] = sum;
  }
  for (i = 0; i < nums_size; i++) {
    for (j = 1; j < nums_size; j++) {
      if (nums_sum[j - 1] > nums_sum[j]) {
        int tmp_sum = nums_sum[j];
        nums_sum[j] = nums_sum[j - 1];
        nums_sum[j - 1] = tmp_sum;
        int tmp_num = nums_ptr[j];
        nums_ptr[j] = nums_ptr[j - 1];
        nums_ptr[j - 1] = tmp_num;
      }
    }
  }
  free(nums_sum);
  return nums_ptr;
}
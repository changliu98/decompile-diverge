bool _can_partition(int* nums, int nums_size, int k) {
  if (nums_size > k) {
    return true;
  }
  bool sums[k];
  for (int i = 0; i < k; i++) {
    sums[i] = false;
  }
  for (int i = 0; i < nums_size; i++) {
    if (sums[0]) {
      return true;
    }
    bool new_sums[k];
    for (int j = 0; j < k; j++) {
      new_sums[j] = false;
    }
    for (int j = 0; j < k; j++) {
      if (sums[j] && !sums[(j + nums[i]) % k]) {
        new_sums[(j + nums[i]) % k] = true;
      }
    }
    for (int j = 0; j < k; j++) {
      if (new_sums[j]) {
        sums[j] = true;
      }
    }
    sums[nums[i] % k] = true;
  }
  return sums[0];
}
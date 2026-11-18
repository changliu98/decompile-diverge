int func0(int nums[], int size) {
  int max_val = INT_MIN;
  int min_val = INT_MAX;
  for (int i = 0; i < size; i++) {
    if (nums[i] > max_val) {
      max_val = nums[i];
    }
    if (nums[i] < min_val) {
      min_val = nums[i];
    }
  }
  return max_val - min_val;
}
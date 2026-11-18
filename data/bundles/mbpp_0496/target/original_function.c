void func0(int nums[], int len, int n, int result[]) {
  qsort(nums, len, sizeof(int), compare);
  for (int i = 0; i < n; i++) {
    result[i] = nums[i];
  }
}
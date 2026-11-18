void func0(int nums[], int size, int n, int result[]) {
  qsort(nums, size, sizeof(int), compare);
  for (int i = 0; i < n; i++) {
    result[i] = nums[i];
  }
}
void findMinMax(long nums[], long *min, long *max) {
  int i;
  for (i = 1; i < 5; i++) {
    if (nums[i] < *min) {
      *min = nums[i];
    }
    if (nums[i] > *max) {
      *max = nums[i];
    }
  }
}
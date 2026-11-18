int func0(int* nums, int numsSize) {
  if (numsSize < 3) {
    return -1;
  }
  int i, j, temp;
  for (i = 0; i < numsSize - 1; i++) {
    for (j = i + 1; j < numsSize; j++) {
      if (nums[i] < nums[j]) {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }
  int a = nums[0] * nums[1] * nums[2];
  int b = nums[numsSize - 1] * nums[numsSize - 2] * nums[0];
  return a > b ? a : b;
}
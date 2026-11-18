void func0(int *nums, int numsSize, int *returnSize) {
  int count = 0;
  int index = 0;
  int i;
  for (i = 0; i < numsSize; i++) {
    if (nums[i] == 0) {
      count++;
    } else {
      returnSize[index++] = nums[i];
    }
  }
  for (i = 0; i < count; i++) {
    returnSize[index++] = 0;
  }
}
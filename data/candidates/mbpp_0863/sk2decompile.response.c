int _longestConsecutive(int *nums, int numsSize) {
  int max = 0;
  int count = 0;
  int i, j;
  for (i = 0; i < numsSize - 1; i++) {
    for (j = 0; j < numsSize - i - 1; j++) {
      if (nums[j] > nums[j + 1]) {
        int temp = nums[j];
        nums[j] = nums[j + 1];
        nums[j + 1] = temp;
      }
    }
  }
  int *newNums = (int *)malloc(numsSize * sizeof(int));
  int newNumsSize = 1;
  newNums[0] = nums[0];
  for (i = 1; i < numsSize; i++) {
    if (nums[i] != nums[i - 1]) {
      newNums[newNumsSize++] = nums[i];
    }
  }
  for (i = 0; i < newNumsSize; i++) {
    if (i > 0 && newNums[i] == newNums[i - 1] + 1) {
      count++;
    } else {
      count = 1;
    }
    if (max < count) {
      max = count;
    }
  }
  free(newNums);
  return max;
}
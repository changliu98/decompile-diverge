void func0(int *nums, int numsSize) {
  int i = 0;
  int j = 0;
  int k = numsSize - 1;
  int temp;
  while (j <= k) {
    if (nums[j] == 0) {
      temp = nums[i];
      nums[i] = nums[j];
      nums[j] = temp;
      i++;
      j++;
    } else if (nums[j] == 1) {
      j++;
    } else {
      temp = nums[j];
      nums[j] = nums[k];
      nums[k] = temp;
      k--;
    }
  }
}
void func0(int *nums, int numsSize, char ***p, int *pSize) {
  char *nums_str[] = {"",   "One",  "Two",   "Three", "Four",
                      "Five", "Six",  "Seven", "Eight", "Nine"};
  int i, j, tmp;
  for (j = 0; j < numsSize - 1; j++) {
    for (i = 0; i < numsSize - j - 1; i++) {
      if (nums[i] > nums[i + 1]) {
        tmp = nums[i];
        nums[i] = nums[i + 1];
        nums[i + 1] = tmp;
      }
    }
  }
  *pSize = 0;
  for (j = numsSize - 1; j >= 0; j--) {
    if (nums[j] >= 1 && nums[j] <= 9) {
      (*pSize)++;
    }
  }
  *p = malloc(sizeof(char *) * (*pSize));
  for (j = numsSize - 1, i = 0; j >= 0 && i < *pSize; j--) {
    if (nums[j] >= 1 && nums[j] <= 9) {
      (*p)[i++] = nums_str[nums[j]];
    }
  }
}
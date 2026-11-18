int removeElement(int *nums,int numsSize,int val)

{
  int i;
  int val_local;
  int numsSize_local;
  int *nums_local;
  
  i = 0;
  numsSize_local = numsSize;
  while (i < numsSize_local) {
    if (nums[i] == val) {
      numsSize_local = numsSize_local + -1;
      nums[i] = nums[numsSize_local];
    }
    else {
      i = i + 1;
    }
  }
  return numsSize_local;
}
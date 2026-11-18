void findMinMax(long *nums,long *min,long *max)

{
  int i;
  long *max_local;
  long *min_local;
  long *nums_local;
  
  for (i = 1; i < 5; i = i + 1) {
    if (nums[i] < *min) {
      *min = nums[i];
    }
    if (*max < nums[i]) {
      *max = nums[i];
    }
  }
  return;
}
longlong func0(longlong *nums,int size)

{
  long local_38;
  int i;
  longlong min;
  longlong current;
  int size_local;
  longlong *nums_local;
  
  current = *nums;
  min = *nums;
  for (i = 1; i < size; i = i + 1) {
    if (current < 0) {
      local_38 = current + nums[i];
    }
    else {
      local_38 = nums[i];
    }
    current = local_38;
    if (local_38 < min) {
      min = local_38;
    }
  }
  return min;
}
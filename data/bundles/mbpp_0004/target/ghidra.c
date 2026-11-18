void func0(int *nums,int size,int n,int *result)

{
  int i;
  int *result_local;
  int n_local;
  int size_local;
  int *nums_local;
  
  qsort(nums,(long)size,4,compare);
  for (i = 0; i < n; i = i + 1) {
    result[i] = nums[i];
  }
  return;
}
void func0(int *nums,int length,int n,int *result)

{
  double dVar1;
  int i;
  int *result_local;
  int n_local;
  int length_local;
  int *nums_local;
  
  for (i = 0; i < length; i = i + 1) {
    dVar1 = pow((double)nums[i],(double)n);
    result[i] = (int)dVar1;
  }
  return;
}
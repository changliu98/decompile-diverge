double func0(int *nums,int n)

{
  double dVar1;
  double ratio;
  int i;
  int n1;
  int n_local;
  int *nums_local;
  
  n1 = 0;
  for (i = 0; i < n; i = i + 1) {
    if (nums[i] == 0) {
      n1 = n1 + 1;
    }
  }
  dVar1 = round(DAT_00102008 * ((double)n1 / (double)n));
  return dVar1 / DAT_00102008;
}
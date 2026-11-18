int func0(int *nums,int length)

{
  int n;
  int i;
  int sum;
  int length_local;
  int *nums_local;
  
  sum = 0;
  for (i = 0; i < length; i = i + 1) {
    n = nums[i];
    if (n < 0) {
      n = -n;
    }
    for (; 0 < n; n = n / 10) {
      sum = n % 10 + sum;
    }
  }
  return sum;
}
int func0(int *nums,int size)

{
  int n;
  int last;
  int first;
  int i;
  int num;
  int size_local;
  int *nums_local;
  
  num = 0;
  for (i = 0; i < size; i = i + 1) {
    if (10 < nums[i]) {
      for (n = nums[i]; 9 < n; n = n / 10) {
      }
      if ((n % 2 == 1) && ((nums[i] % 10) % 2 == 1)) {
        num = num + 1;
      }
    }
  }
  return num;
}
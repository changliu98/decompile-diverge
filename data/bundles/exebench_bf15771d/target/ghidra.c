int computesizes(int *nums,int *narray)

{
  int n;
  int na;
  int a;
  int twotoi;
  int i;
  int *narray_local;
  int *nums_local;
  
  a = 0;
  na = 0;
  n = 0;
  i = 0;
  for (twotoi = 1; twotoi / 2 < *narray; twotoi = twotoi << 1) {
    if ((0 < nums[i]) && (a = nums[i] + a, twotoi / 2 < a)) {
      n = twotoi;
      na = a;
    }
    if (a == *narray) break;
    i = i + 1;
  }
  *narray = n;
  return na;
}
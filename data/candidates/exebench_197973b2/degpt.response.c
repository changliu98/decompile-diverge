void computesizes(int *nums,int ntotal,int *narray,int *nhash)

{
  bool bVar1;
  int local_40;
  int n;
  int na;
  int a;
  int i;
  int *nhash_local;
  int *narray_local;
  int ntotal_local;
  int *nums_local;
  
  na = *nums;
  n = 0;
  if (na == 0) {
    n = -1;
  }
  i = 1;
  a = na;
  while( true ) {
    bVar1 = false;
    if (a < *narray) {
      bVar1 = 1 << ((char)i - 1U & 0x1f) <= *narray;
    }
    if (!bVar1) break;
    if ((0 < nums[i]) && (a = nums[i] + a, 1 << ((char)i - 1U & 0x1f) <= a)) {
      n = i;
      na = a;
    }
    i = i + 1;
  }
  *nhash = ntotal - na;
  if (n == -1) {
    local_40 = 0;
  }
  else {
    local_40 = 1 << ((byte)n & 0x1f);
  }
  *narray = local_40;
  return;
}
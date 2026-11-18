int func0(int *A,int n,int x)

{
  int iVar1;
  int mid;
  int result;
  int right;
  int left;
  int x_local;
  int n_local;
  int *A_local;
  
  left = 0;
  right = n + -1;
  result = -1;
  while (left <= right) {
    iVar1 = left + (right - left) / 2;
    if (x == A[iVar1]) {
      right = iVar1 + -1;
      result = iVar1;
    }
    else if (x < A[iVar1]) {
      right = iVar1 + -1;
    }
    else {
      left = iVar1 + 1;
    }
  }
  return result;
}
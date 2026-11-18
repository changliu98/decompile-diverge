int func0(int *A,int n)

{
  int iVar1;
  int prev;
  int next;
  int mid;
  int right;
  int left;
  int n_local;
  int *A_local;
  
  left = 0;
  right = n + -1;
  while( true ) {
    if (right < left) {
      return -1;
    }
    if (A[left] <= A[right]) break;
    iVar1 = (left + right) / 2;
    if ((A[iVar1] <= A[(iVar1 + 1) % n]) && (A[iVar1] <= A[(iVar1 + -1 + n) % n])) {
      return iVar1;
    }
    if (A[right] < A[iVar1]) {
      if (A[left] <= A[iVar1]) {
        left = iVar1 + 1;
      }
    }
    else {
      right = iVar1 + -1;
    }
  }
  return left;
}
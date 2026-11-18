int func0(int *A,int n)

{
  int iVar1;
  _Bool _Var2;
  int temp;
  int j;
  int i;
  int n_local;
  int *A_local;
  
  for (i = 0; j = i, i < n; i = i + 1) {
    while (j = j + 1, j < n) {
      if (A[j] < A[i]) {
        iVar1 = A[j];
        A[j] = A[i];
        A[i] = iVar1;
      }
    }
  }
  do {
    i = n + -1;
    if (i < 0) {
      return -1;
    }
    _Var2 = is_palindrome(A[i]);
    n = i;
  } while (!_Var2);
  return A[i];
}
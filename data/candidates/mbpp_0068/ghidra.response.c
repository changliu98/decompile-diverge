_Bool func0(int *A,int n)

{
  bool bVar1;
  _Bool local_1d;
  int i;
  _Bool decreasing;
  _Bool increasing;
  int n_local;
  int *A_local;
  
  bVar1 = true;
  decreasing = true;
  for (i = 0; i < n + -1; i = i + 1) {
    if (A[i + 1] < A[i]) {
      bVar1 = false;
    }
    if (A[i] < A[i + 1]) {
      decreasing = false;
    }
  }
  local_1d = true;
  if (!bVar1) {
    local_1d = decreasing;
  }
  return local_1d;
}
int func0(int *A, int n)
{
 int look_up[200];
 int i;
 if (n == 1)
  return A[0];
 look_up[0] = A[0];
 look_up[1] = A[1] > A[0] ? A[0] : A[1];
 for (i = 2; i < n; i++) {
  look_up[i] = A[i] + look_up[i - 2] > look_up[i - 1] ? look_up[i - 1] : A[i] + look_up[i - 2];
  look_up[i] = look_up[i] > A[i] ? A[i] : look_up[i];
 }
 return look_up[n - 1];
}
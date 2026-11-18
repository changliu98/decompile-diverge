void mult(double *A,double *a,double *b)

{
  int iVar1;
  int i;
  int c;
  double *b_local;
  double *a_local;
  double *A_local;
  
  i = 0;
  for (c = 0; c < 4; c = c + 1) {
    b[c] = A[i] * *a;
    b[c] = A[i + 1] * a[1] + b[c];
    iVar1 = i + 3;
    b[c] = A[i + 2] * a[2] + b[c];
    i = i + 4;
    b[c] = A[iVar1] * a[3] + b[c];
  }
  return;
}
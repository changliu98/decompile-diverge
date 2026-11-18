int func0(int *a,int *b,int n)

{
  int iVar1;
  int i;
  int sum;
  int n_local;
  int *b_local;
  int *a_local;
  
  sort(a,n);
  sort(b,n);
  sum = 0;
  for (i = 0; i < n; i = i + 1) {
    iVar1 = abs(a[i] - b[i]);
    sum = iVar1 + sum;
  }
  return sum;
}
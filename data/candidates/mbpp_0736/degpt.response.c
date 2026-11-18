int func0(int *a,int n,int x)

{
  int iVar1;
  int mid;
  int r;
  int l;
  int x_local;
  int n_local;
  int *a_local;
  
  l = 0;
  iVar1 = n;
  while (r = iVar1, l < r) {
    iVar1 = (l + r) / 2;
    if (a[iVar1] < x) {
      l = iVar1 + 1;
      iVar1 = r;
    }
  }
  return l;
}
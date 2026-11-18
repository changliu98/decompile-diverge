int func0(int n)

{
  int iVar1;
  int i;
  int sm;
  int j;
  int n_local;
  
  sm = 0;
  for (i = 1; i <= n; i = i + 1) {
    iVar1 = i * 2 + -1;
    sm = iVar1 * iVar1 * iVar1 * iVar1 * iVar1 + sm;
  }
  return sm;
}
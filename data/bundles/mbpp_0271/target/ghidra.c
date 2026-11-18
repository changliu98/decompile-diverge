long func0(int n)

{
  int iVar1;
  int j;
  int i;
  long sum;
  int n_local;
  
  sum = 0;
  for (i = 1; i <= n; i = i + 1) {
    iVar1 = i * 2;
    sum = iVar1 * iVar1 * iVar1 * iVar1 * iVar1 + sum;
  }
  return sum;
}
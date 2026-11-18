int func0(int n)

{
  int iVar1;
  int iVar2;
  int n_local;
  
  iVar1 = factorial(n + 1,n << 1);
  iVar2 = factorial(1,n);
  return iVar1 / iVar2;
}
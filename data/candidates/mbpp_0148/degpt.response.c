int func0(int N)

{
  int iVar1;
  int iVar2;
  int A;
  int N_local;
  
  iVar1 = closest(N);
  iVar2 = sum_digits_single(iVar1);
  iVar1 = sum_digits_single(N - iVar1);
  return iVar2 + iVar1;
}
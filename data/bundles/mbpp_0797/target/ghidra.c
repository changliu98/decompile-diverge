int func0(int l,int r)

{
  int iVar1;
  int iVar2;
  int r_local;
  int l_local;
  
  iVar1 = sum_Odd(r);
  iVar2 = sum_Odd(l + -1);
  return iVar1 - iVar2;
}
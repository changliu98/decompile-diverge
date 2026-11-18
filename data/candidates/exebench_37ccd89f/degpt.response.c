void ft_ultimate_div_mod(int *a,int *b)

{
  int iVar1;
  int iVar2;
  int d;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  iVar2 = *b;
  *b = *a - (iVar1 / iVar2) * *b;
  *a = iVar1 / iVar2;
  return;
}
void ft_swap(int *a,int *b)

{
  int iVar1;
  int num;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  *a = *b;
  *b = iVar1;
  return;
}
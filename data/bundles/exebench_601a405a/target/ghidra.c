void simple_sort_swapper(int *one,int *two)

{
  int iVar1;
  int aux;
  int *two_local;
  int *one_local;
  
  iVar1 = *one;
  *one = *two;
  *two = iVar1;
  return;
}
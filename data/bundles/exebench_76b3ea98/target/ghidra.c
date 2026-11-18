void swap_ints(int *i,int *j)

{
  int iVar1;
  int temp;
  int *j_local;
  int *i_local;
  
  iVar1 = *i;
  *i = *j;
  *j = iVar1;
  return;
}
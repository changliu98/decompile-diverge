void swap(int *i,int *j)

{
  int iVar1;
  int temp;
  int *j_local;
  int *i_local;
  
  iVar1 = *j;
  *j = *i;
  *i = iVar1;
  return;
}
void swap(int *i1,int *i2)

{
  int iVar1;
  int temp;
  int *i2_local;
  int *i1_local;
  
  iVar1 = *i1;
  *i1 = *i2;
  *i2 = iVar1;
  return;
}
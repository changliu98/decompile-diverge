void swap(int *item1,int *item2)

{
  int iVar1;
  int tmp;
  int *item2_local;
  int *item1_local;
  
  iVar1 = *item1;
  *item1 = *item2;
  *item2 = iVar1;
  return;
}
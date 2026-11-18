void swap(int *ptr1,int *ptr2)

{
  int iVar1;
  int temp;
  int *ptr2_local;
  int *ptr1_local;
  
  iVar1 = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = iVar1;
  return;
}
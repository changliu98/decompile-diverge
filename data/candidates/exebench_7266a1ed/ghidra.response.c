void swap(int *left,int *right)

{
  int iVar1;
  int temp;
  int *right_local;
  int *left_local;
  
  iVar1 = *left;
  *left = *right;
  *right = iVar1;
  return;
}
void swap(int *ptrX,int *ptrY)

{
  int iVar1;
  int temp;
  int *ptrY_local;
  int *ptrX_local;
  
  iVar1 = *ptrX;
  *ptrX = *ptrY;
  *ptrY = iVar1;
  return;
}
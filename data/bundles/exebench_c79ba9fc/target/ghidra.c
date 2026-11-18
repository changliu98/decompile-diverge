void swap(int *x,int *y)

{
  int iVar1;
  int temp;
  int *y_local;
  int *x_local;
  
  if ((x != (int *)0x0) && (y != (int *)0x0)) {
    iVar1 = *x;
    *x = *y;
    *y = iVar1;
  }
  return;
}
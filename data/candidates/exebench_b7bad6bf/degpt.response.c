int swap(int *x,int *y)

{
  int iVar1;
  int tmp;
  int *y_local;
  int *x_local;
  
  iVar1 = *x;
  *x = *y;
  *y = iVar1;
  return 0;
}
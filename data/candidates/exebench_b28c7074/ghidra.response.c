void swap(int *px,int *py)

{
  int iVar1;
  int temp;
  int *py_local;
  int *px_local;
  
  iVar1 = *px;
  *px = *py;
  *py = iVar1;
  return;
}
int doit(int *x,int y)

{
  int iVar1;
  int y_local;
  int *x_local;
  uint local_c;
  
  iVar1 = *x;
  if (y < iVar1) {
    *x = y;
  }
  local_c = (uint)(y < iVar1);
  return local_c;
}
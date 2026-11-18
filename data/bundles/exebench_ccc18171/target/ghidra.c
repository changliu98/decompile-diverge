int ok_smul4(int x,int y,int *dest)

{
  int iVar1;
  uchar byte_result;
  int *dest_local;
  int y_local;
  int x_local;
  
  iVar1 = (int)((long)x * (long)y);
  *dest = iVar1;
  return (int)((long)iVar1 == (long)x * (long)y);
}
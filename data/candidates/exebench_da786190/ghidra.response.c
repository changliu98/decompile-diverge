void SetBitInt(int *x,int bitNum)

{
  int bitNum_local;
  int *x_local;
  
  *x = 1 << ((byte)bitNum & 0x1f) | *x;
  return;
}
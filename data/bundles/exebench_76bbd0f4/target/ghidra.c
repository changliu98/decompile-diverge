void assignops(int *x,int y)

{
  int y_local;
  int *x_local;
  
  *x = *x >> ((byte)y & 0x1f);
  *x = *x << ((byte)y & 0x1f);
  *x = y + *x;
  *x = y * *x;
  *x = *x / y;
  *x = y ^ *x;
  *x = *x - y;
  *x = y & *x;
  *x = y | *x;
  *x = *x % y;
  *x = y;
  return;
}
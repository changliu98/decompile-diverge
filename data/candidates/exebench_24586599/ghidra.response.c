void set_bit(int *n,int b)

{
  int b_local;
  int *n_local;
  
  *n = 1 << ((byte)b & 0x1f) | *n;
  return;
}
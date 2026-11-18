int set_bit(int *ptr,int n)

{
  int n_local;
  int *ptr_local;
  
  *ptr = *ptr | 1 << ((byte)n & 0x1f);
  return *ptr;
}
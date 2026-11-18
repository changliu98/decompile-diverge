unsigned_long xorshf96(unsigned_long *x,unsigned_long *y,unsigned_long *z)

{
  ulong uVar1;
  unsigned_long t;
  unsigned_long *z_local;
  unsigned_long *y_local;
  unsigned_long *x_local;
  
  *x = *x << 0x10 ^ *x;
  *x = *x >> 5 ^ *x;
  *x = *x << 1 ^ *x;
  uVar1 = *x;
  *x = *y;
  *y = *z;
  *z = uVar1 ^ *x ^ *y;
  return *z;
}
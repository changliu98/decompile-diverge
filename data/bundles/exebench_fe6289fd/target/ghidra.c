unsigned_long xchg8(unsigned_long *ptr,unsigned_long x)

{
  unsigned_long uVar1;
  unsigned_long __x;
  unsigned_long x_local;
  unsigned_long *ptr_local;
  
  LOCK();
  uVar1 = *ptr;
  *ptr = x;
  UNLOCK();
  return uVar1;
}
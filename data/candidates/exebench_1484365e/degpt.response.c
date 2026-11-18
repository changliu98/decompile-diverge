int atomic32_increment(int *dest)

{
  int iVar1;
  int r;
  int *dest_local;
  
  LOCK();
  iVar1 = *dest;
  *dest = *dest + 1;
  UNLOCK();
  return iVar1 + 1;
}
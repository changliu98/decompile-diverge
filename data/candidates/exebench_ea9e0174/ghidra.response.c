int atomic_add(int *ptr,int incr)

{
  int iVar1;
  int incr_local;
  int *ptr_local;
  
  LOCK();
  iVar1 = *ptr;
  *ptr = *ptr + incr;
  UNLOCK();
  return iVar1;
}
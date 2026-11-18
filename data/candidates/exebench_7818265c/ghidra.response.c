int xchg(int *addr,int newval)

{
  int iVar1;
  int result;
  int newval_local;
  int *addr_local;
  
  LOCK();
  iVar1 = *addr;
  *addr = newval;
  UNLOCK();
  return iVar1;
}
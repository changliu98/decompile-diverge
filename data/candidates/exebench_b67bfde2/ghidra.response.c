int wdl_atomic_incr(int *v)

{
  int iVar1;
  int *v_local;
  
  LOCK();
  iVar1 = *v;
  *v = *v + 1;
  UNLOCK();
  return iVar1 + 1;
}
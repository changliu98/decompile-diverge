int _hclib_atomic_dec_relaxed(int *target)

{
  int iVar1;
  int *target_local;
  
  LOCK();
  iVar1 = *target;
  *target = *target + -1;
  UNLOCK();
  return iVar1 + -1;
}
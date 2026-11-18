void atomic_and(size_t *x,size_t val)

{
  size_t sVar1;
  bool bVar2;
  ulong local_20;
  size_t val_local;
  size_t *x_local;
  
  local_20 = *x;
  do {
    LOCK();
    sVar1 = *x;
    bVar2 = local_20 == sVar1;
    if (bVar2) {
      *x = local_20 & val;
      sVar1 = local_20;
    }
    UNLOCK();
    local_20 = sVar1;
  } while (!bVar2);
  return;
}
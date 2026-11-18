void StoreUintptr(uintptr_t *addr,uintptr_t val)

{
  uintptr_t uVar1;
  uintptr_t v;
  uintptr_t val_local;
  uintptr_t *addr_local;
  
  v = *addr;
  while( true ) {
    LOCK();
    uVar1 = *addr;
    if (v == uVar1) {
      *addr = val;
    }
    UNLOCK();
    if (v == uVar1) break;
    v = *addr;
  }
  return;
}
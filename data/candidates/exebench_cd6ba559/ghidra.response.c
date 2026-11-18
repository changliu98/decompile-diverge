uintptr_t AddUintptr(uintptr_t *val,uintptr_t delta)

{
  uintptr_t uVar1;
  uintptr_t delta_local;
  uintptr_t *val_local;
  
  LOCK();
  uVar1 = *val;
  *val = *val + delta;
  UNLOCK();
  return uVar1 + delta;
}
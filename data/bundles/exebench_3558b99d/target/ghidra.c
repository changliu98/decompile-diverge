long ff_atomic_dec_long(long *val)

{
  long lVar1;
  long *val_local;
  
  LOCK();
  lVar1 = *val;
  *val = *val + -1;
  UNLOCK();
  return lVar1 + -1;
}
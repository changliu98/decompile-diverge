unsigned_long ihk_atomic_add_long_return(long i,long *v)

{
  long lVar1;
  long __i;
  long *v_local;
  long i_local;
  
  LOCK();
  lVar1 = *v;
  *v = *v + i;
  UNLOCK();
  return lVar1 + i;
}
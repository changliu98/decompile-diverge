void atomic_dec(int *v)

{
  int *v_local;
  
  LOCK();
  *v = *v + -1;
  UNLOCK();
  return;
}
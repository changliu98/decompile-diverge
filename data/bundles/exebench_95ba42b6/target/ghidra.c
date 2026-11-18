void atomic_inc(int *v)

{
  int *v_local;
  
  LOCK();
  *v = *v + 1;
  UNLOCK();
  return;
}
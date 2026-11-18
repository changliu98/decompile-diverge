void atomic_retain(int *p)

{
  int *p_local;
  
  LOCK();
  *p = *p + 1;
  UNLOCK();
  return;
}
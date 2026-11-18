void atomic_inc(int *a)

{
  int *a_local;
  
  LOCK();
  *a = *a + 1;
  UNLOCK();
  return;
}
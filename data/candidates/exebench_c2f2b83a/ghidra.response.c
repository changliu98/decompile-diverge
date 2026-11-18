void a_inc(int *p)

{
  int *p_local;
  
  LOCK();
  *p = *p + 1;
  UNLOCK();
  return;
}
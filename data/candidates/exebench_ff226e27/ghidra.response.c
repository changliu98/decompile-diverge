void atomic_add(int i,long *v)

{
  long *v_local;
  int i_local;
  
  LOCK();
  *(int *)v = (int)*v + i;
  UNLOCK();
  return;
}
void a_or(int *p,int v)

{
  int v_local;
  int *p_local;
  
  LOCK();
  *p = *p | v;
  UNLOCK();
  return;
}
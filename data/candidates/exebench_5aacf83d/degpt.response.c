int a_swap(int *p,int v)

{
  int iVar1;
  int v_local;
  int *p_local;
  
  LOCK();
  iVar1 = *p;
  *p = v;
  UNLOCK();
  return iVar1;
}
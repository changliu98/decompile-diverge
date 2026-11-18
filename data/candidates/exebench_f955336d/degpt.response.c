int a_fetch_add(int *x,int v)

{
  int iVar1;
  int v_local;
  int *x_local;
  
  LOCK();
  iVar1 = *x;
  *x = *x + v;
  UNLOCK();
  return iVar1;
}
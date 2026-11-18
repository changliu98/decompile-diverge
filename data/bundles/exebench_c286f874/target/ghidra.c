int fetch_and_add(int *p,int i)

{
  int iVar1;
  int i_local;
  int *p_local;
  
  LOCK();
  iVar1 = *p;
  *p = *p + i;
  UNLOCK();
  return iVar1;
}
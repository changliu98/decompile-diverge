int atomic_sub(int *i,int j)

{
  int iVar1;
  int j_local;
  int *i_local;
  
  LOCK();
  iVar1 = *i;
  *i = *i - j;
  UNLOCK();
  return iVar1;
}
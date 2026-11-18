int a_swap(int *x,int v)

{
  int iVar1;
  int iVar2;
  int old;
  int v_local;
  int *x_local;
  
  do {
    iVar2 = *x;
    LOCK();
    iVar1 = *x;
    if (iVar2 == iVar1) {
      *x = v;
    }
    UNLOCK();
  } while (iVar2 != iVar1);
  return iVar2;
}
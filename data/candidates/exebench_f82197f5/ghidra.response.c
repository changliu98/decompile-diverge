void UNLOCK(int *f)

{
  int iVar1;
  int old;
  int *f_local;
  
  LOCK();
  iVar1 = *f;
  *f = *f + -1;
  UNLOCK();
  if ((iVar1 != 1) && (iVar1 == 2)) {
    LOCK();
    *f = 0;
    UNLOCK();
    syscall(0xca,f,1);
  }
  return;
}
int atomic_add32_ret(int *cnt)

{
  int iVar1;
  int __c;
  int *cnt_local;
  
  LOCK();
  iVar1 = *cnt;
  *cnt = *cnt + 1;
  UNLOCK();
  return iVar1;
}
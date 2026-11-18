int cond_read_lock(int *lk)

{
  int iVar1;
  int result;
  int *lk_local;
  
  iVar1 = *lk;
  if (-1 < iVar1) {
    *lk = *lk + 1;
  }
  result = (int)(-1 < iVar1);
  return result;
}
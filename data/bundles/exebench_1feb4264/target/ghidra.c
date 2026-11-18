int atomicCompareAndSwap(int *var,int ov,int nv)

{
  int iVar1;
  int rv;
  int nv_local;
  int ov_local;
  int *var_local;
  
  LOCK();
  iVar1 = *var;
  if (ov == iVar1) {
    *var = nv;
    iVar1 = ov;
  }
  UNLOCK();
  return iVar1;
}
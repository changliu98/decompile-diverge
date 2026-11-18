int atomicDecrement(int *var)

{
  int iVar1;
  int ov;
  int *var_local;
  
  LOCK();
  iVar1 = *var;
  *var = *var + -1;
  UNLOCK();
  return iVar1 + -1;
}
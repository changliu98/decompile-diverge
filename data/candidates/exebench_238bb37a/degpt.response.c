long incr(long *p,long val)

{
  long lVar1;
  long y;
  long x;
  long val_local;
  long *p_local;
  
  lVar1 = *p;
  *p = lVar1 + val;
  return lVar1;
}
void swap(long *xp,long *yp)

{
  long lVar1;
  long t1;
  long t0;
  long *yp_local;
  long *xp_local;
  
  lVar1 = *xp;
  *xp = *yp;
  *yp = lVar1;
  return;
}
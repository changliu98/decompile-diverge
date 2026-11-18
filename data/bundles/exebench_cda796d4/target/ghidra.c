void swap(long *p1,long *p2)

{
  long lVar1;
  long tmp;
  long *p2_local;
  long *p1_local;
  
  lVar1 = *p1;
  *p1 = *p2;
  *p2 = lVar1;
  return;
}
void swap_l(long *a,long *b)

{
  long lVar1;
  long tmp;
  long *b_local;
  long *a_local;
  
  lVar1 = *a;
  *a = *b;
  *b = lVar1;
  return;
}
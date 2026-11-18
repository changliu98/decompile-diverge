void check_long(long *x,long *y,char *ret)

{
  char cVar1;
  char *ret_local;
  long *y_local;
  long *x_local;
  
  cVar1 = 'f';
  if ((long)y - (long)x == 8) {
    cVar1 = 't';
  }
  *ret = cVar1;
  return;
}
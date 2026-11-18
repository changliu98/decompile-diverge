void check_int(int *x,int *y,char *ret)

{
  char cVar1;
  char *ret_local;
  int *y_local;
  int *x_local;
  
  cVar1 = 'f';
  if ((long)y - (long)x == 4) {
    cVar1 = 't';
  }
  *ret = cVar1;
  return;
}
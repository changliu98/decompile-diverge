char * ReadNumber(char *s,double *num)

{
  bool bVar1;
  int x2;
  int x1;
  double minus;
  double x3;
  double *num_local;
  char *s_local;
  char *local_10;
  
  minus = DAT_00102008;
  s_local = s;
  while( true ) {
    bVar1 = true;
    if (*s_local != '+') {
      bVar1 = *s_local == '-';
    }
    if (!bVar1) break;
    if (*s_local == '-') {
      minus = -minus;
    }
    s_local = s_local + 1;
  }
  x2 = 0;
  x1 = 0;
  x3 = DAT_00102008;
  while( true ) {
    bVar1 = false;
    if (*s_local < ':') {
      bVar1 = '/' < *s_local;
    }
    if (!bVar1) break;
    x1 = x1 * 10 + (int)*s_local + -0x30;
    s_local = s_local + 1;
  }
  if (*s_local == '\0') {
    *num = (double)x1 * minus;
    local_10 = s_local;
  }
  else {
    if (*s_local == '.') {
      while( true ) {
        s_local = s_local + 1;
        bVar1 = false;
        if ('/' < *s_local) {
          bVar1 = *s_local < ':';
        }
        if (!bVar1) break;
        x2 = x2 * 10 + (int)*s_local + -0x30;
        x3 = DAT_00102010 * x3;
      }
    }
    *num = minus * ((double)x1 + (double)x2 / x3);
    local_10 = s_local;
  }
  return local_10;
}
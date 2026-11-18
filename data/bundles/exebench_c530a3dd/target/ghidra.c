uint str_copy(char *s,char *t)

{
  char cVar1;
  int len;
  char *t_local;
  char *s_local;
  
  len = 0;
  t_local = t;
  s_local = s;
  while( true ) {
    cVar1 = *t_local;
    *s_local = cVar1;
    if (cVar1 == '\0') {
      return len;
    }
    cVar1 = t_local[1];
    s_local[1] = cVar1;
    if (cVar1 == '\0') {
      return len + 1;
    }
    cVar1 = t_local[2];
    s_local[2] = cVar1;
    if (cVar1 == '\0') {
      return len + 2;
    }
    cVar1 = t_local[3];
    s_local[3] = cVar1;
    if (cVar1 == '\0') break;
    s_local = s_local + 4;
    t_local = t_local + 4;
    len = len + 4;
  }
  return len + 3;
}
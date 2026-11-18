char * strichr(char *p,int c)

{
  char *t;
  int c_local;
  char *p_local;
  
  t = p;
  if (p != (char *)0x0) {
    for (; *t != '\0'; t = t + 1) {
    }
    for (; p <= t; t = t + -1) {
      t[1] = *t;
    }
    *p = (char)c;
  }
  return p;
}
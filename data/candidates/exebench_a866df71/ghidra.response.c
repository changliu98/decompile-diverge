char * skip(char *s,char c)

{
  bool bVar1;
  char c_local;
  char *s_local;
  
  s_local = s;
  while( true ) {
    bVar1 = false;
    if (*s_local != c) {
      bVar1 = *s_local != '\0';
    }
    if (!bVar1) break;
    s_local = s_local + 1;
  }
  if (*s_local != '\0') {
    *s_local = '\0';
    s_local = s_local + 1;
  }
  return s_local;
}
void replaceChar(char *s,char oldc,char newc)

{
  char c;
  char newc_local;
  char oldc_local;
  char *s_local;
  
  s_local = s;
  if (s != (char *)0x0) {
    for (; *s_local != '\0'; s_local = s_local + 1) {
      if (*s_local == oldc) {
        *s_local = newc;
      }
    }
  }
  return;
}
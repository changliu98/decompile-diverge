int tt_unesc(char *s,char esc)

{
  int n;
  char *dst;
  char *src;
  char esc_local;
  char *s_local;
  
  n = 0;
  src = s;
  while( true ) {
    if (*src == esc) {
      dst = src;
      for (; *src != '\0'; src = src + 1) {
        if (*src == esc) {
          src = src + 1;
          n = n + 1;
        }
        *dst = *src;
        dst = dst + 1;
      }
      return n;
    }
    if (*src == '\0') break;
    src = src + 1;
  }
  return 0;
}
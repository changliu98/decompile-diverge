char * fix(char *d,char *s)

{
  int di;
  int i;
  char *s_local;
  char *d_local;
  
  di = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    if (s[i] == '\b') {
      di = di + -1;
      if (di < 0) {
        di = 0;
      }
    }
    else {
      d[di] = s[i];
      di = di + 1;
    }
  }
  d[di] = '\0';
  return d;
}
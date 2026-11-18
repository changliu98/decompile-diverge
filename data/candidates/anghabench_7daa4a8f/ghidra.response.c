char * stb_skipnewline(char *s)

{
  char *s_local;
  
  s_local = s;
  if ((*s == '\r') || (*s == '\n')) {
    if ((int)*s + (int)s[1] == 0x17) {
      s_local = s + 1;
    }
    s_local = s_local + 1;
  }
  return s_local;
}
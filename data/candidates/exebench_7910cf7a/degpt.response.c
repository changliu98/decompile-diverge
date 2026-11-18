char * strset(char *str,int c)

{
  char *s;
  int c_local;
  char *str_local;
  
  s = str;
  while (*s != '\0') {
    *s = (char)c;
    s = s + 1;
  }
  return str;
}
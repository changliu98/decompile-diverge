void gdb_strcpy(char *buf,char *s)

{
  char *s_local;
  char *buf_local;
  
  s_local = s;
  buf_local = buf;
  while (*s_local != '\0') {
    *buf_local = *s_local;
    s_local = s_local + 1;
    buf_local = buf_local + 1;
  }
  *buf_local = '\0';
  return;
}
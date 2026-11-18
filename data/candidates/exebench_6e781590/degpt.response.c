void replace_char(char *buf,char from,char to)

{
  char to_local;
  char from_local;
  char *buf_local;
  
  for (buf_local = buf; *buf_local != '\0'; buf_local = buf_local + 1) {
    if (*buf_local == from) {
      *buf_local = to;
    }
  }
  return;
}
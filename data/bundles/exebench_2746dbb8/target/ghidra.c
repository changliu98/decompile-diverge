void _uc(char *buf)

{
  char *buf_local;
  
  for (buf_local = buf; *buf_local != '\0'; buf_local = buf_local + 1) {
    if (('`' < *buf_local) && (*buf_local < '{')) {
      *buf_local = *buf_local + -0x20;
    }
  }
  return;
}
void charset_remove(char *buffer,char value)

{
  char *r;
  char *l;
  char value_local;
  char *buffer_local;
  
  l = buffer;
  for (r = buffer; *r != '\0'; r = r + 1) {
    if (*r != value) {
      *l = *r;
      l = l + 1;
    }
  }
  *l = '\0';
  return;
}
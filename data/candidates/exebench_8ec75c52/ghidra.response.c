void strupr(char *str)

{
  char *str_local;
  
  for (str_local = str; *str_local != '\0'; str_local = str_local + 1) {
    if (('`' < *str_local) && (*str_local < '{')) {
      *str_local = *str_local + -0x20;
    }
  }
  return;
}
void string_rip(char *str,char *ripper)

{
  bool bVar1;
  int skip_this;
  char *ripper_idx;
  char *t_ptr;
  char *ripper_local;
  char *str_local;
  
  t_ptr = str;
  str_local = str;
  do {
    if (*str_local == '\0') {
      *t_ptr = '\0';
      return;
    }
    bVar1 = false;
    for (ripper_idx = ripper; *ripper_idx != '\0'; ripper_idx = ripper_idx + 1) {
      if (*str_local == *ripper_idx) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      *t_ptr = *str_local;
      t_ptr = t_ptr + 1;
    }
    str_local = str_local + 1;
  } while( true );
}
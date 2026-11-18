void ck_encrypt(char *s)

{
  char *s_local;
  
  for (s_local = s; *s_local != '\0'; s_local = s_local + 1) {
    if (((*s_local != 'p') && (*s_local != '\\')) && (*s_local != 'S')) {
      *s_local = *s_local ^ 0xf;
    }
  }
  return;
}
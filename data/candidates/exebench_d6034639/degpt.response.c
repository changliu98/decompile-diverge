int fatfs_get_sfn_display_name(char *out,char *in)

{
  char *pcVar1;
  char a;
  int len;
  char *in_local;
  char *out_local;
  
  len = 0;
  in_local = in;
  out_local = out;
  while (*in_local != '\0' && len < 0xc) {
    pcVar1 = in_local + 1;
    a = *in_local;
    in_local = pcVar1;
    if (a != ' ') {
      if (('@' < a) && (a < '[')) {
        a = a + ' ';
      }
      *out_local = a;
      len = len + 1;
      out_local = out_local + 1;
    }
  }
  *out_local = '\0';
  return 1;
}
_Bool wc_unescape(char *output,char *wildcard)

{
  char *pcVar1;
  char *wildcard_local;
  char *output_local;
  
  pcVar1 = wildcard;
  output_local = output;
  while( true ) {
    while( true ) {
      wildcard_local = pcVar1;
      if (*wildcard_local == '\0') {
        if (output_local != (char *)0x0) {
          *output_local = '\0';
        }
        return true;
      }
      if (*wildcard_local != '\\') break;
      pcVar1 = wildcard_local + 1;
      if (*pcVar1 != '\0') {
        if (output_local != (char *)0x0) {
          *output_local = *pcVar1;
          output_local = output_local + 1;
        }
        pcVar1 = wildcard_local + 2;
      }
    }
    if ((((*wildcard_local == '*') || (*wildcard_local == '?')) || (*wildcard_local == '[')) ||
       (*wildcard_local == ']')) break;
    if (output_local != (char *)0x0) {
      *output_local = *wildcard_local;
      output_local = output_local + 1;
    }
    pcVar1 = wildcard_local + 1;
  }
  return false;
}
char * char_replace(char *str,char o,char n)

{
  char *pcVar1;
  char *p;
  char n_local;
  char o_local;
  char *str_local;
  
  if ((str != (char *)0x0) && (p = str, *str != '\0')) {
    while (pcVar1 = strchr(p,(int)o), pcVar1 != (char *)0x0) {
      p = pcVar1 + 1;
      *pcVar1 = n;
    }
  }
  return str;
}
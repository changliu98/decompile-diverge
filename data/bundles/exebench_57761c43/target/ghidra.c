void char_replace(char *str,char origc,char newc)

{
  char *pcVar1;
  char newc_local;
  char origc_local;
  char *str_local;
  
  str_local = str;
  while (pcVar1 = str_local + 1, *str_local != '\0') {
    str_local = pcVar1;
    if (*pcVar1 == origc) {
      *pcVar1 = newc;
    }
  }
  return;
}
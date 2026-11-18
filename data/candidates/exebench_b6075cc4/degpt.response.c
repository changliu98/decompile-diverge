void break_atr(char *str,char c)

{
  char *pcVar1;
  char *p;
  char c_local;
  char *str_local;
  
  pcVar1 = strrchr(str,(int)c);
  if (pcVar1 != (char *)0x0) {
    *pcVar1 = '\0';
  }
  return;
}
void stress_chop(char *str,char ch)

{
  char *pcVar1;
  char *ptr;
  char ch_local;
  char *str_local;
  
  pcVar1 = strchr(str,(int)ch);
  if (pcVar1 != (char *)0x0) {
    *pcVar1 = '\0';
  }
  return;
}
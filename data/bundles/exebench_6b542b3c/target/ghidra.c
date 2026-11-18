char * trim(char *str,char *trim_chars)

{
  char *pcVar1;
  bool bVar2;
  char *endstr;
  char *trim_chars_local;
  char *str_local;
  
  if (str != (char *)0x0) {
    endstr = index(str,0);
    while( true ) {
      endstr = endstr + -1;
      bVar2 = false;
      if (str <= endstr) {
        pcVar1 = index(trim_chars,(int)*endstr);
        bVar2 = pcVar1 != (char *)0x0;
      }
      if (!bVar2) break;
      *endstr = '\0';
    }
  }
  return str;
}
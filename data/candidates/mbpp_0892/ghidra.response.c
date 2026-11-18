char * func0(char *text)

{
  int iVar1;
  char *pcVar2;
  int err;
  char *bufptr;
  char *cursor;
  regmatch_t match;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  bufptr = func0::buffer;
  iVar1 = regcomp((regex_t *)&regex," +",1);
  cursor = text;
  if (iVar1 == 0) {
    for (; *cursor != '\0'; cursor = cursor + match.rm_eo) {
      iVar1 = regexec((regex_t *)&regex,cursor,1,(regmatch_t *)&match,0);
      if (iVar1 != 0) {
        strcpy(bufptr,cursor);
        break;
      }
      memcpy(bufptr,cursor,(long)match.rm_so);
      pcVar2 = bufptr + match.rm_so;
      bufptr = pcVar2 + 1;
      *pcVar2 = ' ';
    }
    regfree((regex_t *)&regex);
    local_10 = func0::buffer;
  }
  else {
    local_10 = (char *)0x0;
  }
  return local_10;
}
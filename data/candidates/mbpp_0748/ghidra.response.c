void func0(char *str1,char *result)

{
  int iVar1;
  char *cursor;
  char buffer [1024];
  regmatch_t matches [3];
  regex_t regex;
  char *result_local;
  char *str1_local;
  
  regcomp((regex_t *)&regex,"([a-z])([A-Z])",1);
  strcpy(buffer,str1);
  cursor = buffer;
  *result = '\0';
  while( true ) {
    iVar1 = regexec((regex_t *)&regex,cursor,3,(regmatch_t *)matches,0);
    if (iVar1 != 0) break;
    strncat(result,cursor,(long)matches[1].rm_eo);
    strcat(result," ");
    cursor = cursor + matches[2].rm_so;
  }
  strcat(result,cursor);
  regfree((regex_t *)&regex);
  return;
}
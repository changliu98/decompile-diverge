_Bool func0(char *string)

{
  int iVar1;
  _Bool match_found;
  int result;
  regex_t regex;
  char *string_local;
  
  regcomp((regex_t *)&regex,".*[0-9]$",0);
  iVar1 = regexec((regex_t *)&regex,string,0,(regmatch_t *)0x0,0);
  regfree((regex_t *)&regex);
  return iVar1 == 0;
}
char * func0(char *string)

{
  int iVar1;
  char *pattern;
  int result;
  regex_t regex;
  char *string_local;
  char *local_10;
  
  regcomp((regex_t *)&regex,"^[aeiouAEIOU][A-Za-z0-9_]*",9);
  iVar1 = regexec((regex_t *)&regex,string,0,(regmatch_t *)0x0,0);
  regfree((regex_t *)&regex);
  if (iVar1 == 0) {
    local_10 = "Valid";
  }
  else {
    local_10 = "Invalid";
  }
  return local_10;
}
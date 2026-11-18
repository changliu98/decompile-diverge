char * func0(char *string)

{
  int iVar1;
  regmatch_t matches [1];
  int ret;
  char *regex;
  regex_t reg;
  char *string_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&reg,"[a-zA-Z0-9]$",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&reg,string,1,(regmatch_t *)matches,0);
    regfree((regex_t *)&reg);
    if (iVar1 == 0) {
      local_10 = "Accept";
    }
    else {
      local_10 = "Discard";
    }
  }
  else {
    local_10 = "Error compiling regex";
  }
  return local_10;
}
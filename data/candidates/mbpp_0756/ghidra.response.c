char * func0(char *text)

{
  int iVar1;
  char *result;
  int ret;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"ab?",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    if (iVar1 == 0) {
      result = "Found a match!";
    }
    else {
      result = "Not matched!";
    }
    regfree((regex_t *)&regex);
    local_10 = result;
  }
  else {
    local_10 = "Not matched!";
  }
  return local_10;
}
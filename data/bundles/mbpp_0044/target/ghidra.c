char * func0(char *text)

{
  int iVar1;
  char *pattern;
  int result;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"^[[:alnum:]_]+",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_10 = "Found a match!";
    }
    else {
      local_10 = "Not matched!";
    }
  }
  else {
    local_10 = "Regex compilation error";
  }
  return local_10;
}
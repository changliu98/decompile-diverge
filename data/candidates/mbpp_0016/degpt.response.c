char * func0(char *text)

{
  int iVar1;
  int reti;
  char *pattern;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  regcomp((regex_t *)&regex,"^[a-z]+_[a-z]+$",1);
  iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
  regfree((regex_t *)&regex);
  if (iVar1 == 0) {
    local_10 = "Found a match!";
  }
  else {
    local_10 = "Not matched!";
  }
  return local_10;
}
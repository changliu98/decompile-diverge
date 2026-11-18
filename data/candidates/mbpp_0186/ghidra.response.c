char * func0(char *text,char *pattern)

{
  int iVar1;
  int reti;
  regex_t regex;
  char *pattern_local;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,pattern,0);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_10 = "Matched!";
    }
    else {
      local_10 = "Not Matched!";
    }
  }
  else {
    local_10 = "Regex compilation failed!";
  }
  return local_10;
}
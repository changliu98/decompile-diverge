char * func0(char *text)

{
  int iVar1;
  char *patterns;
  int ret;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"ab*?",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_10 = "Found a match!";
    }
    else if (iVar1 == 1) {
      local_10 = "Not matched!";
    }
    else {
      local_10 = "Regex match failed";
    }
  }
  else {
    local_10 = "Error compiling regex";
  }
  return local_10;
}
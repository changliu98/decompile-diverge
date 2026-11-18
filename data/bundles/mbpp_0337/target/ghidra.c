char * func0(char *text)

{
  int iVar1;
  regmatch_t matches [1];
  char *patterns;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"\\w+\\S*$",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,1,(regmatch_t *)matches,0);
    if (iVar1 == 0) {
      regfree((regex_t *)&regex);
      local_10 = "Found a match!";
    }
    else {
      regfree((regex_t *)&regex);
      local_10 = "Not matched!";
    }
  }
  else {
    local_10 = "Regex compilation failed";
  }
  return local_10;
}
char * func0(char *text)

{
  int iVar1;
  char *pattern;
  char *match_result;
  int result;
  regex_t regex;
  char *text_local;
  
  regcomp((regex_t *)&regex,"ab{2,3}",1);
  iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
  if (iVar1 == 0) {
    match_result = "Found a match!";
  }
  else {
    match_result = "Not matched!";
  }
  regfree((regex_t *)&regex);
  return match_result;
}
int func0(char *pattern,char *text,int *start,int *end)

{
  int iVar1;
  int status;
  regmatch_t match;
  regex_t regex;
  int *end_local;
  int *start_local;
  char *text_local;
  char *pattern_local;
  int local_c;
  
  iVar1 = regcomp((regex_t *)&regex,pattern,1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,1,(regmatch_t *)&match,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      *start = match.rm_so;
      *end = match.rm_eo;
      local_c = 0;
    }
    else {
      local_c = -1;
    }
  }
  else {
    local_c = -1;
  }
  return local_c;
}
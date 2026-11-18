char * func0(char *text)

{
  int iVar1;
  char error_message [100];
  char *pattern;
  int reti;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"\\w*z.\\w*",1);
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
      regerror(iVar1,(regex_t *)&regex,error_message,100);
      fprintf(*(FILE **)PTR_stderr_00103ff8,"Regex match failed: %s\n",error_message);
      local_10 = "Regex match error";
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
    local_10 = "Regex compile error";
  }
  return local_10;
}
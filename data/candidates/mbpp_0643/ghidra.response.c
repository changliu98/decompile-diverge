char * func0(char *text)

{
  int iVar1;
  char msgbuf [100];
  int reti;
  char *pattern;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"\\Bz\\B",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    if (iVar1 == 0) {
      local_10 = "Found a match!";
    }
    else if (iVar1 == 1) {
      local_10 = "Not matched!";
    }
    else {
      regerror(iVar1,(regex_t *)&regex,msgbuf,100);
      fprintf(*(FILE **)PTR_stderr_00103ff8,"Regex match failed: %s\n",msgbuf);
      local_10 = "Regex execution error";
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
    local_10 = "Regex compilation error";
  }
  return local_10;
}
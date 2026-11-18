char * func0(char *string)

{
  int iVar1;
  char msgbuf [100];
  int reti;
  regex_t regex;
  char *string_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"^[a-z]$|^([a-z]).*\\1$",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,string,0,(regmatch_t *)0x0,0);
    if (iVar1 == 0) {
      regfree((regex_t *)&regex);
      local_10 = "Valid";
    }
    else if (iVar1 == 1) {
      regfree((regex_t *)&regex);
      local_10 = "Invalid";
    }
    else {
      regerror(iVar1,(regex_t *)&regex,msgbuf,100);
      fprintf(*(FILE **)PTR_stderr_00103ff8,"Regex match failed: %s\n",msgbuf);
      regfree((regex_t *)&regex);
      local_10 = "Invalid";
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
    local_10 = "Invalid";
  }
  return local_10;
}
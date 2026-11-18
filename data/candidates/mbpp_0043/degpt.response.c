char * func0(char *text)

{
  int iVar1;
  char errorMessage [100];
  char *patterns;
  int regexSearch;
  int regexInit;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"^[a-z]+_[a-z]+$",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    if (iVar1 == 0) {
      regfree((regex_t *)&regex);
      local_10 = "Found a match!";
    }
    else if (iVar1 == 1) {
      regfree((regex_t *)&regex);
      local_10 = "Not matched!";
    }
    else {
      regerror(iVar1,(regex_t *)&regex,errorMessage,100);
      fprintf(*(FILE **)PTR_stderr_00103ff8,"Regex match failed: %s\n",errorMessage);
      regfree((regex_t *)&regex);
      local_10 = "Error occurred";
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
    local_10 = "Compilation error";
  }
  return local_10;
}
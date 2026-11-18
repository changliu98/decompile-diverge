_Bool func0(char *string)

{
  int iVar1;
  int result;
  regex_t regex;
  char *string_local;
  _Bool local_9;
  
  iVar1 = regcomp((regex_t *)&regex,"^5",0);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,string,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_9 = true;
    }
    else {
      local_9 = false;
    }
  }
  else {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
    local_9 = false;
  }
  return local_9;
}
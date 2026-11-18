char * func0(char *email)

{
  int iVar1;
  int ret;
  regex_t regex;
  char *regex_pattern;
  char *email_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$",9);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,email,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_10 = "Valid Email";
    }
    else {
      local_10 = "Invalid Email";
    }
  }
  else {
    local_10 = "Invalid Email";
  }
  return local_10;
}
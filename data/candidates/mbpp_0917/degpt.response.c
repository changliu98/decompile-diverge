char * func0(char *text)

{
  int iVar1;
  char *patterns;
  int reti;
  regex_t regex;
  char *text_local;
  char *local_10;
  
  regcomp((regex_t *)&regex,"[A-Z]+[a-z]+$",1);
  iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
  if (iVar1 == 0) {
    local_10 = "Found a match!";
  }
  else {
    local_10 = "Not matched!";
  }
  return local_10;
}
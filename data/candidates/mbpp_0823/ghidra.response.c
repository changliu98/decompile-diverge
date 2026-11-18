char * func0(char *string,char *sample)

{
  int iVar1;
  char *pcVar2;
  char pattern [100];
  int result;
  regex_t regex;
  char *sample_local;
  char *string_local;
  char *local_10;
  
  pcVar2 = strstr(string,sample);
  if (pcVar2 == (char *)0x0) {
    local_10 = "entered string isnt a substring";
  }
  else {
    memset(pattern,0,100);
    pattern[0] = '^';
    strcat(pattern,sample);
    regcomp((regex_t *)&regex,pattern,0);
    iVar1 = regexec((regex_t *)&regex,string,0,(regmatch_t *)0x0,0);
    regfree((regex_t *)&regex);
    if (iVar1 == 0) {
      local_10 = "string starts with the given substring";
    }
    else {
      local_10 = "string doesnt start with the given substring";
    }
  }
  return local_10;
}
char * func0(char *text)

{
  int iVar1;
  char word [100];
  int end;
  int start;
  regmatch_t match [1];
  regex_t regex;
  char *text_local;
  char *local_10;
  
  iVar1 = regcomp((regex_t *)&regex,"\\w+ly",1);
  if (iVar1 == 0) {
    iVar1 = regexec((regex_t *)&regex,text,1,(regmatch_t *)match,0);
    if (iVar1 == 0) {
      strncpy(word,text + match[0].rm_so,(long)(match[0].rm_eo - match[0].rm_so));
      word[match[0].rm_eo - match[0].rm_so] = '\0';
      snprintf(func0::result,100,"%d-%d: %s",(ulong)(uint)match[0].rm_so,(ulong)(uint)match[0].rm_eo
               ,word);
      regfree((regex_t *)&regex);
      local_10 = func0::result;
    }
    else {
      regfree((regex_t *)&regex);
      local_10 = (char *)0x0;
    }
  }
  else {
    printf("Could not compile regex\n");
    local_10 = (char *)0x0;
  }
  return local_10;
}
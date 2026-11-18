char * func0(char *item)

{
  regoff_t rVar1;
  int iVar2;
  size_t sVar3;
  char *__dest;
  long lVar4;
  long lVar5;
  int end;
  int start;
  char *result;
  regmatch_t matches [2];
  regex_t regex;
  char *item_local;
  
  sVar3 = strlen(item);
  __dest = malloc(sVar3 + 1);
  strcpy(__dest,item);
  iVar2 = regcomp((regex_t *)&regex," ?\\([^)]+\\)",1);
  if (iVar2 == 0) {
    while (iVar2 = regexec((regex_t *)&regex,__dest,2,(regmatch_t *)matches,0),
          rVar1 = matches[0].rm_eo, iVar2 == 0) {
      lVar4 = (long)matches[0].rm_so;
      lVar5 = (long)matches[0].rm_eo;
      sVar3 = strlen(__dest);
      memmove(__dest + lVar4,__dest + lVar5,(sVar3 - (long)rVar1) + 1);
    }
    regfree((regex_t *)&regex);
  }
  return __dest;
}
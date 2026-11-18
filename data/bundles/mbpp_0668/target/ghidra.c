char * func0(char *string,char *charToReplace)

{
  int iVar1;
  long lVar2;
  size_t sVar3;
  long lVar4;
  long lVar5;
  size_t pos;
  char *result;
  size_t offset;
  regmatch_t match;
  char pattern [10];
  regex_t regex;
  char *charToReplace_local;
  char *string_local;
  char *local_10;
  
  sprintf(pattern,"%s{2,}",charToReplace);
  iVar1 = regcomp((regex_t *)&regex,pattern,1);
  if (iVar1 == 0) {
    offset = 0;
    local_10 = strdup(string);
    while( true ) {
      iVar1 = regexec((regex_t *)&regex,local_10 + offset,1,(regmatch_t *)&match,0);
      if (iVar1 != 0) break;
      lVar2 = offset + (long)match.rm_so;
      lVar4 = (long)match.rm_eo;
      lVar5 = (long)match.rm_so;
      sVar3 = strlen(local_10);
      memmove(local_10 + lVar2 + 1,local_10 + ((lVar4 + lVar2) - lVar5),
              ((sVar3 - lVar2) - (long)match.rm_eo) + (long)match.rm_so + 1);
      offset = lVar2 + 1;
    }
    regfree((regex_t *)&regex);
  }
  else {
    local_10 = (char *)0x0;
  }
  return local_10;
}
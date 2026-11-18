char * func0(char *ip)

{
  int iVar1;
  size_t sVar2;
  char *__dest;
  long lVar3;
  size_t end;
  size_t start;
  size_t len;
  char *current_location;
  char *result;
  char pattern [5];
  regmatch_t matches [1];
  regex_t regex;
  char *ip_local;
  
  pattern._0_4_ = DAT_00102004;
  pattern[4] = DAT_00102008;
  sVar2 = strlen(ip);
  __dest = malloc(sVar2 + 1);
  regcomp((regex_t *)&regex,pattern,1);
  strcpy(__dest,ip);
  current_location = __dest;
  while( true ) {
    iVar1 = regexec((regex_t *)&regex,current_location,1,(regmatch_t *)matches,0);
    if (iVar1 != 0) break;
    sVar2 = strlen(current_location);
    lVar3 = (long)matches[0].rm_so;
    memmove(current_location + lVar3 + 1,current_location + matches[0].rm_eo,
            (sVar2 - (long)matches[0].rm_eo) + 1);
    current_location = current_location + lVar3 + 1;
  }
  regfree((regex_t *)&regex);
  return __dest;
}
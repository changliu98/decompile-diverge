char *func0(char *ip)
{
  char *ret;
  char *p;
  char *re = "\\.0+";
  struct regex_t re_t;
  struct regmatch_t match;
  unsigned long len;
  unsigned long offset;
  ret = (char *)malloc(strlen(ip)+1);
  regcomp(&re_t,re,1);
  strcpy(ret,ip);
  for(p = ret; !regexec(&re_t, p, 1, &match, 0); p += offset + 1){
    len = strlen(p);
    offset = match.rm_so;
    memmove(p + match.rm_so + 1, p + match.rm_eo, len - match.rm_eo + 1);
  }
  regfree(&re_t);
  return ret;
}
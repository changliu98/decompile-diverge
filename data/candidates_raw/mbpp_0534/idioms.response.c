int regex_match(char *pattern, char *text, int *start, int *end)
{
  int ret;
  struct regmatch_t match;
  struct regex_t re;
  if (regcomp(&re, pattern, 1))
    return -1;
  ret = regexec(&re, text, 1, &match, 0);
  regfree(&re);
  if (ret)
    return -1;
  *start = match.rm_so;
  *end = match.rm_eo;
  return 0;
}
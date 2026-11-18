char *func0(char *item)
{
  char *ret = (char *)malloc((strlen(item)+1)*sizeof(char));
  strcpy(ret, item);
  struct regex_t re;
  if (regcomp(&re, " ?\\([^)]+\\)", 1) == 0) {
    struct regmatch_t pm[2];
    while (regexec(&re, ret, 2, pm, 0) == 0) {
      int end = pm[0].rm_eo;
      char *start = &ret[pm[0].rm_so];
      char *endp = &ret[pm[0].rm_eo];
      memmove(start, endp, (strlen(ret)-end)+1);
    }
    regfree(&re);
  }
  return ret;
}
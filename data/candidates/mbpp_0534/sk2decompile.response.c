int _regex_match(const char *pattern, const char *string, int *start,
                 int *end) {
  regex_t preg;
  int r;
  regmatch_t pmatch;
  r = regcomp(&preg, pattern, 1);
  if (r != 0) return -1;
  r = regexec(&preg, string, 1, &pmatch, 0);
  regfree(&preg);
  if (r != 0) return -1;
  *start = pmatch.rm_so;
  *end = pmatch.rm_eo;
  return 0;
}
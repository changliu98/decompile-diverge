char *_remove_parentheses(char *s) {
  char *t;
  regex_t re;
  regmatch_t rm[2];
  int rc;
  t = malloc(strlen(s) + 1);
  strcpy(t, s);
  rc = regcomp(&re, " ?\\([^)]+\\)", 1);
  if (rc == 0) {
    while (regexec(&re, t, 2, rm, 0) == 0) {
      int start = rm[0].rm_so;
      int end = rm[0].rm_eo;
      memmove(t + start, t + end, strlen(t) - end + 1);
    }
    regfree(&re);
  }
  return t;
}
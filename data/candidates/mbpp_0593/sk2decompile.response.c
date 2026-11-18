char *func0(char *str) {
  char pattern[] = "\\.0+";
  char *ret = malloc(strlen(str) + 1);
  regex_t preg;
  regcomp(&preg, pattern, 1);
  strcpy(ret, str);
  char *p = ret;
  regmatch_t pmatch[1];
  while (!regexec(&preg, p, 1, pmatch, 0)) {
    memmove(p + pmatch[0].rm_so + 1, p + pmatch[0].rm_eo,
            strlen(p) - pmatch[0].rm_eo + 1);
    p += pmatch[0].rm_so + 1;
  }
  regfree(&preg);
  return ret;
}
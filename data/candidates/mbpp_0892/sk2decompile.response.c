char *_glp_lib_word_wrap(const char *str) {
  static char buf[1024];
  const char *p = str;
  char *q = buf;
  regex_t re;
  int ret;
  regmatch_t match;
  regoff_t off;
  ret = regcomp(&re, " +", 1);
  if (ret) return NULL;
  while (*p) {
    ret = regexec(&re, p, 1, &match, 0);
    if (ret) {
      strcpy(q, p);
      break;
    }
    memcpy(q, p, match.rm_so);
    q += match.rm_so;
    *q++ = ' ';
    p += match.rm_eo;
  }
  regfree(&re);
  return buf;
}
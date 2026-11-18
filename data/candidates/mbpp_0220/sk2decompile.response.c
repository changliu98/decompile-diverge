char *func0(char *s, int n) {
  static char buf[1000];
  regex_t re;
  regmatch_t rm;
  int i;
  strcpy(buf, s);
  regcomp(&re, "[ ,.]", 1);
  for (i = 0; i < n && !regexec(&re, buf, 1, &rm, 0); i++) {
    buf[rm.rm_so] = ':';
  }
  regfree(&re);
  return buf;
}
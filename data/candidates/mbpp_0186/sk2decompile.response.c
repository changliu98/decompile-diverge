char *func0(char *s, char *p) {
  regex_t re;
  int ret;
  ret = regcomp(&re, p, 0);
  if (ret) {
    return "Regex compilation failed!";
  }
  ret = regexec(&re, s, 0, NULL, 0);
  regfree(&re);
  if (!ret) {
    return "Matched!";
  }
  return "";
}
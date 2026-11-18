int _is_number(char *str) {
  regex_t preg;
  int ret;
  regcomp(&preg, ".*[0-9]$", 0);
  ret = !regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  return ret;
}
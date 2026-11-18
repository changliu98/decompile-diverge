char *func0(char *str) {
  regex_t preg;
  int x;
  char *ret;
  x = regcomp(&preg, "ab?", 1);
  x = regexec(&preg, str, 0, NULL, 0);
  if (x == 0) {
    ret = "Found a match!";
  } else {
    ret = "Not matched!";
  }
  regfree(&preg);
  return ret;
}
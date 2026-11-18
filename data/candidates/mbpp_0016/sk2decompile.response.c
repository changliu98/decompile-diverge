char *func0(char *str) {
  regex_t preg;
  int x;
  regcomp(&preg, "^[a-z]+_[a-z]+$", 1);
  x = regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  if (!x) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}
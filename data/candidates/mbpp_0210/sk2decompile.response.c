int _check_for_illegal_char(char *str) {
  regex_t preg;
  int x;
  regcomp(&preg, "[^a-zA-Z0-9.]", 1);
  x = regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  if (x == 1)
    return 1;
  else
    return 0;
}
char* func0(char* str) {
  regex_t preg;
  int x;
  regcomp(&preg, "[A-Z]+[a-z]+$", 1);
  x = regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  if (x == 0) {
    return "Yes";
  } else {
    return "No";
  }
}
char *func0(char *str) {
  regex_t preg;
  int x;
  regcomp(&preg, "^[aeiouAEIOU][A-Za-z0-9_]*", 1 | 8);
  x = regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  if (!x)
    return "Valid";
  else
    return "Invalid";
}
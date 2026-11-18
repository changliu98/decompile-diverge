char *func0(const char *text, const char *pattern) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, pattern, 0);
  if (reti) {
    return ("Regex compilation failed!");
  }
  reti = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return ("Matched!");
  }
  else {
    return ("Not Matched!");
  }
}
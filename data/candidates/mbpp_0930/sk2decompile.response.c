char *func0(char *str) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "ab*?", 1);
  if (reti) {
    return "Error compiling regex";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return "Found a match!";
  }
  if (reti == 1) {
    return "Not matched!";
  }
  return "Regex match failed";
}
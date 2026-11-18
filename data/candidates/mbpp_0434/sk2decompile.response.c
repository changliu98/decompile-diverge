char *func0(char *str) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "ab+", 1);
  if (reti) {
    return "Regex compilation failed!";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}
char *func0(char *str) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "a.*?b$", 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Error";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return "Found a match!";
  } else if (reti == REG_NOMATCH) {
    return "Not matched!";
  }
  return "Error";
}
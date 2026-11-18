char *func0(char *data) {
  regex_t regex;
  int reti;
  char *msg;
  regcomp(&regex, "ab{2,3}", 1);
  reti = regexec(&regex, data, 0, NULL, 0);
  if (!reti) {
    msg = "Found a match!";
  } else if (reti == REG_NOMATCH) {
    msg = "Not matched!";
  }
  regfree(&regex);
  return msg;
}
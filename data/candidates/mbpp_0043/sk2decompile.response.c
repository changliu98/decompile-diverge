char *func0(char *str) {
  regex_t regex;
  char *pattern = "^[a-z]+_[a-z]+$";
  int reti;
  reti = regcomp(&regex, pattern, 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Compilation error";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  if (!reti) {
    regfree(&regex);
    return "Found a match!";
  } else if (reti == 1) {
    regfree(&regex);
    return "Not matched!";
  } else {
    char msgbuf[100];
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    regfree(&regex);
    return "Error occurred";
  }
}
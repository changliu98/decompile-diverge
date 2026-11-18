char *func0(char *str) {
  int reti;
  regex_t regex;
  char msgbuf[100];
  reti = regcomp(&regex, "^[a-z]$|^([a-z]).*\\1$", 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Invalid";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  if (!reti) {
    regfree(&regex);
    return "Valid";
  } else if (reti == 1) {
    regfree(&regex);
    return "Invalid";
  } else {
    regerror(reti, &regex, msgbuf, 100);
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    regfree(&regex);
    return "Invalid";
  }
}
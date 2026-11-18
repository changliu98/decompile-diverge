char *func0(char *str) {
  int reti;
  regex_t regex;
  char *pattern = "\\w*z.\\w*";
  reti = regcomp(&regex, pattern, 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compile error";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return "Found a match!";
  } else if (reti == 1) {
    return "Not matched!";
  } else {
    char msgbuf[100];
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    return "Regex match error";
  }
}
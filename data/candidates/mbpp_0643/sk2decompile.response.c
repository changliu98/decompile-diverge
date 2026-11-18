char *func0(char *str) {
  int reti;
  char *regex = "\\Bz\\B";
  regex_t regex;
  char msgbuf[100];
  reti = regcomp(&regex, regex, 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  if (!reti) {
    return "Found a match!";
  } else if (reti == 1) {
    return "Not matched!";
  } else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    return "Regex execution error";
  }
}
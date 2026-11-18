char* func0(const char* string) {
  regex_t regex;
  int reti;
  char msgbuf[100];
  reti = regcomp(&regex, "^[a-z]$|^([a-z]).*\\1$", REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Invalid";
  }
  reti = regexec(&regex, string, 0, NULL, 0);
  if (!reti) {
    regfree(&regex);
    return "Valid";
  }
  else if (reti == REG_NOMATCH) {
    regfree(&regex);
    return "Invalid";
  }
  else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    regfree(&regex);
    return "Invalid";
  }
}
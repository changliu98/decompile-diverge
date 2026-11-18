char *func0(char *patterns[], int patterns_count, char *line) {
  regex_t regex;
  int reti;
  char *msg;
  int i = 0;

  while(1) {
    if (i >= patterns_count) break;

    reti = regcomp(&regex, patterns[i], 0);
    if (reti) {
      fprintf(stderr, "Could not compile regex\n");
      msg = "Not Matched!";
      return msg;
    }

    reti = regexec(&regex, line, 0, NULL, 0);
    if (!reti) {
      regfree(&regex);
      msg = "Matched!";
      return msg;
    }
    else if (reti == REG_NOMATCH) {
      regfree(&regex);
      i++;
    }
    else {
      fprintf(stderr, "Regex match error: %d\n", reti);
      msg = "Not Matched!";
      return msg;
    }
  }

  msg = "Not Matched!";
  return msg;
}
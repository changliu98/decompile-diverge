char *func0(char *data) {
  regex_t re;
  int reti;
  reti = regcomp(&re, "ab{3}", 1);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  reti = regexec(&re, data, 0, NULL, 0);
  regfree(&re);
  if (!reti) {
    return "Found a match!";
  } else if (reti == REG_NOMATCH) {
    return "Not matched!";
  }
  return "Regex match error";
}
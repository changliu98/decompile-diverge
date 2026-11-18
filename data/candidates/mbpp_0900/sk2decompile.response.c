bool _is_five(const char *str) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "^5", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return false;
  }
  reti = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (reti != 0) {
    return false;
  }
  return true;
}
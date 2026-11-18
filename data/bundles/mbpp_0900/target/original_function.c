bool func0(const char *string) {
  regex_t regex;
  int result;
  result = regcomp(&regex, "^5", 0);
  if (result) {
    fprintf(stderr, "Could not compile regex\n");
    return false;
  }
  result = regexec(&regex, string, 0, NULL, 0);
  regfree(&regex);
  if (result == 0) {
    return true;
  } else {
    return false;
  }
}
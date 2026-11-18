bool func0(const char* string) {
  regex_t regex;
  int result;
  regcomp(&regex, "[^a-zA-Z0-9.]", REG_EXTENDED);
  result = regexec(&regex, string, 0, NULL, 0);
  regfree(&regex);
  return result == REG_NOMATCH;
}
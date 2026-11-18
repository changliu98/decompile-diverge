bool func0(const char *string) {
  regex_t regex;
  int result;
  bool match_found;
  regcomp(&regex, ".*[0-9]$", 0);
  result = regexec(&regex, string, 0, NULL, 0);
  match_found = (result == 0);
  regfree(&regex);
  return match_found;
}
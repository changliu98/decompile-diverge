char *func0(const char *text) {
  regex_t regex;
  int result;
  char *pattern = "a.*?b$";
  result = regcomp(&regex, pattern, REG_EXTENDED);
  if (result) {
    return ("Regex compilation failed.");
  }
  result = regexec(&regex, text, 0, NULL, 0);
  if (!result) {
    return ("Found a match!");
  } else if (result == REG_NOMATCH) {
    return ("Not matched!");
  } else {
    return ("Regex match failed.");
  }
  regfree(&regex);
}
char* func0(const char* text) {
  regex_t regex;
  int ret;
  char* patterns = "ab*?";
  ret = regcomp(&regex, patterns, REG_EXTENDED);
  if (ret) {
    return "Error compiling regex";
  }
  ret = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!ret) {
    return "Found a match!";
  } else if (ret == REG_NOMATCH) {
    return "Not matched!";
  } else {
    return "Regex match failed";
  }
}
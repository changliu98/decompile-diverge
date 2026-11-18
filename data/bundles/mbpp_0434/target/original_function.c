const char* func0(const char* text) {
  regex_t regex;
  int ret;
  ret = regcomp(&regex, "ab+", REG_EXTENDED);
  if (ret) {
    return "Regex compilation failed!";
  }
  ret = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (ret == 0) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}
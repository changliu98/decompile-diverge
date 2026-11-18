const char *func0(const char *string) {
  regex_t regex;
  int ret = regcomp(&regex, "[a-zA-Z0-9]$", 1);
  if (ret) {
    return "Error compiling regex";
  }

  regmatch_t matches[1];
  ret = regexec(&regex, string, 1, matches, 0);
  regfree(&regex);
  if (!ret) {
    return "Accept";
  }

  return "Discard";
}
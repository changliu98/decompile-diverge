const char *func0(const char *string) {
  regex_t reg;
  const char *regex = "[a-zA-Z0-9]$";
  int ret;
  ret = regcomp(&reg, regex, REG_EXTENDED);
  if (ret) {
    return "Error compiling regex";
  }
  regmatch_t matches[1];
  ret = regexec(&reg, string, 1, matches, 0);
  regfree(&reg);
  if (!ret) {
    return "Accept";
  } else {
    return "Discard";
  }
}
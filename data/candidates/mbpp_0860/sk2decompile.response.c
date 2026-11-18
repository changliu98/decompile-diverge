char *func0(char *str) {
  regex_t regex;
  char *pattern = "[a-zA-Z0-9]$";
  int status;
  regmatch_t pmatch[1];
  status = regcomp(&regex, pattern, 1);
  if (status) {
    return "Error compiling regex";
  }
  status = regexec(&regex, str, 1, pmatch, 0);
  regfree(&regex);
  if (status) {
    return "Discard";
  }
  return "Accept";
}
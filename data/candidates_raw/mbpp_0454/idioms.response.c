char *regex_test(char *text)
{
  char *pattern = "\\w*z.\\w*";
  char error_message[100];
  int ret;
  struct regex_t re;
  if (regcomp(&re, pattern, 1)) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compile error";
  }
  ret = regexec(&re, text, 0, ((void *)0), 0);
  if (ret == 0) {
    return "Found a match!";
  }
  if (ret == 1) {
    return "Not matched!";
  }
  regerror(ret, &re, error_message, sizeof(error_message));
  fprintf(stderr, "Regex match failed: %s\n", error_message);
  return "Regex match error";
}
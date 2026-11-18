char *regex_test(char *text)
{
  int ret;
  char *str = text;
  struct regex_t regex;
  if (regcomp(&regex, "a.*?b$", 1)) {
    fprintf(stderr, "Could not compile regex\n");
    return "Error";
  }
  ret = regexec(&regex, str, 0, ((void *)0), 0);
  regfree(&regex);
  if (ret == 0)
    return "Found a match!";
  else
    return "Not matched!";
}
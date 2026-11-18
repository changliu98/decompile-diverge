char *regex_test(char *text)
{
  char *pattern = "^[a-z]+_[a-z]+$";
  int ret;
  char errstr[100];
  struct regex_t regex;
  if (regcomp(&regex, pattern, 1)) {
    fprintf(stderr, "Could not compile regex\n");
    return "Compilation error";
  }
  ret = regexec(&regex, text, 0, ((void *)0), 0);
  if (ret == 0) {
    regfree(&regex);
    return "Found a match!";
  }
  else if (ret == 1) {
    regfree(&regex);
    return "Not matched!";
  }
  else {
    regerror(ret, &regex, errstr, sizeof(errstr));
    fprintf(stderr, "Regex match failed: %s\n", errstr);
    regfree(&regex);
    return "Error occurred";
  }
}
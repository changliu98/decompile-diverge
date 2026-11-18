char *func0(char *text)
{
  int ret;
  struct regex_t re;
  char *str = text;
  if (regcomp(&re, "ab{3}", 1)) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  ret = regexec(&re, str, 0, ((void *)0), 0);
  regfree(&re);
  if (ret == 0)
    return "Found a match!";
  else
    return "Not matched!";
}
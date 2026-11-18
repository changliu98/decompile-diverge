char *func0(char *text)
{
  int ret;
  char *str = text;
  struct regex_t re;
  regcomp(&re, "^[a-z]+_[a-z]+$", 1);
  ret = regexec(&re, str, 0, ((void *)0), 0);
  regfree(&re);
  if (ret == 0)
    return "Found a match!";
  else
    return "Not matched!";
}
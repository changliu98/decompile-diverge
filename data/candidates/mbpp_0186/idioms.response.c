char *func0(char *text, char *pattern)
{
  int ret;
  struct regex_t re;
  if (regcomp(&re, pattern, 0))
    return "Regex compilation failed!";
  ret = regexec(&re, text, 0, ((void *)0), 0);
  regfree(&re);
  if (ret == 0)
    return "Matched!";
  return "";
}
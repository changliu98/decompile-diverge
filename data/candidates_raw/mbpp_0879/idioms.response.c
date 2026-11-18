char *regex_test(char *text)
{
  int ret;
  struct regex_t re;
  if (regcomp(&re, "a.*?b$", 1))
    return "Regex compilation failed.";
  ret = regexec(&re, text, 0, ((void *)0), 0);
  if (ret == 0)
    return "Found a match!";
  if (ret == 1)
    return "Not matched!";
  return "Regex match failed.";
}
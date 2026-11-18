char *func0(char *text)
{
  int ret;
  struct regex_t regex;
  if (regcomp(&regex, "ab*?", 1))
    return "Error compiling regex";
  ret = regexec(&regex, text, 0, ((void *)0), 0);
  regfree(&regex);
  if (ret == 0)
    return "Found a match!";
  if (ret == 1)
    return "Not matched!";
  return "Regex match failed";
}
char *check_end(char *str)
{
  int ret;
  struct regmatch_t matches[1];
  struct regex_t re;
  char *re_str = "[a-zA-Z0-9]$";
  ret = regcomp(&re, re_str, 1);
  if (ret != 0)
  {
    return "Error compiling regex";
  }
  ret = regexec(&re, str, 1, matches, 0);
  regfree(&re);
  if (ret == 0)
  {
    return "Accept";
  }
  return "Discard";
}
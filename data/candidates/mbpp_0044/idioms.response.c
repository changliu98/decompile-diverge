char *func0(char *text)
{
  char *re = "^[[:alnum:]_]+";
  int ret;
  struct regex_t re_comp;
  if (regcomp(&re_comp, re, 1))
    return "Regex compilation error";
  ret = regexec(&re_comp, text, 0, ((void *)0), 0);
  regfree(&re_comp);
  if (ret)
    return "Not matched!";
  return "Found a match!";
}
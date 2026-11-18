int is_five(char *str)
{
  struct regex_t re;
  char *re_str = "^5";
  int ret;
  if (regcomp(&re, re_str, 0))
  {
    fprintf(stderr, "Could not compile regex\n");
    return 0;
  }
  ret = regexec(&re, str, 0, ((void *)0), 0);
  regfree(&re);
  if (ret)
  {
    return 0;
  }
  return 1;
}
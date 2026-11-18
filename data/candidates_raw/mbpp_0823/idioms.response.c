char *check_substring(char *string, char *sample)
{
  int ret;
  char *retstr;
  char pattern[100];
  struct regex_t re;
  if (strstr(string, sample) == ((void *)0))
    return "entered string isnt a substring";
  memset(pattern, '\0', 100);
  pattern[0] = '^';
  strcat(pattern, sample);
  regcomp(&re, pattern, 0);
  ret = regexec(&re, string, 0, ((void *)0), 0);
  regfree(&re);
  if (ret == 0)
    retstr = "string starts with the given substring";
  else
    retstr = "string doesnt start with the given substring";
  return retstr;
}
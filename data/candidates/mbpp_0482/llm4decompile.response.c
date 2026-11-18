char *
func0 (char *str)
{
  regex_t regex;
  int ret;
  char *pattern = "[A-Z]+[a-z]+$";

  regcomp (&regex, pattern, 1);
  ret = regexec (&regex, str, 0, NULL, 0);
  regfree (&regex);

  if (!ret)
    return "Yes";
  else
    return "No";
}
char *regex_example(char *text)
{
  char *result;
  char *str = text;
  struct regex r;
  regcomp(&r, "ab{2,3}", 1);
  if (regexec(&r, str, 0, ((void *)0), 0))
    result = "Not matched!";
  else
    result = "Found a match!";
  regfree(&r);
  return result;
}
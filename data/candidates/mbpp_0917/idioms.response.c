char *func0(char *text)
{
  char *text_to_test = text;
  int error;
  struct regex_t regex;
  regcomp(&regex, "[A-Z]+[a-z]+$", 1);
  error = regexec(&regex, text_to_test, 0, ((void *)0), 0);
  if (error)
    return "Not matched!";
  else
    return "Found a match!";
}
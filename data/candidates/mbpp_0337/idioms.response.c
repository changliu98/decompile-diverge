char *func0(char *text)
{
  int ret;
  struct regmatch_t matches[1];
  struct regex_t regex;
  char *pattern = "\\w+\\S*$";
  if (regcomp(&regex, pattern, 1))
    return "Regex compilation failed";
  if (regexec(&regex, text, 1, matches, 0))
  {
    regfree(&regex);
    return "Not matched!";
  }
  else
  {
    regfree(&regex);
    return "Found a match!";
  }
}
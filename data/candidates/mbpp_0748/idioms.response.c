void func0(char *str, char *result)
{
  char buffer[1024];
  struct regmatch_t matches[3];
  struct regex_t regex;
  char *cursor;
  regcomp(&regex, "([a-z])([A-Z])", 1);
  strcpy(buffer, str);
  cursor = buffer;
  *result = '\0';
  while (!regexec(&regex, cursor, 3, matches, 0))
  {
    strncat(result, cursor, matches[1].rm_eo);
    strcat(result, " ");
    cursor += matches[2].rm_so;
  }
  strcat(result, cursor);
  regfree(&regex);
}
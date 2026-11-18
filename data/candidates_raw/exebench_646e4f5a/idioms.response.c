void remove_chars(char *str, char *chars)
{
  int i; int j; int k; int found;
  for (i = j = 0; str[i]; i++)
  {
    found = 0;
    for (k = 0; (chars[k] && (found != 1)); k++)
    {
      if (str[i] == chars[k])
        found = 1;
    }
    if (!found)
      str[j++] = str[i];
  }
  str[j] = '\0';
}
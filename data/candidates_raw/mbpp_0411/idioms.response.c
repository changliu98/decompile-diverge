char *str_to_cap(char *str, char *capstr)
{
  int i = 0;
  int j = 0;
  int cap = 1;
  for (i = 0; str[i]; i++)
  {
    if (str[i] == '_')
    {
      cap = 1;
    }
    else if (cap)
    {
      capstr[j++] = toupper(str[i]);
      cap = 0;
    }
    else
    {
      capstr[j++] = str[i];
    }
  }
  capstr[j] = '\0';
  return capstr;
}
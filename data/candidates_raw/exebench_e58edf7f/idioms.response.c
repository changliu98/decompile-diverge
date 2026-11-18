void toUpper(char *str)
{
  int i = 0;
  for (i = 0; str[i] != '\0'; i++)
  {
    char c = 'a';
    for (c = 'a'; c <= 'z'; c++)
    {
      if (str[i] == c)
      {
        str[i] = c - 32;
      }
    }
  }
}
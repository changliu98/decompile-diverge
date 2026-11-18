void __cdecl sort(char *str)
{
  char t;
  int j, i;

  for (j = 1; j < 10; ++j)
  {
    for (i = 0; i < 10 - j && str[i] != 0; ++i)
    {
      if (str[i] > str[i + 1])
      {
        t = str[i];
        str[i] = str[i + 1];
        str[i + 1] = t;
      }
    }
  }
}
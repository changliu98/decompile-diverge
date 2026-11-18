int func0(char *str)
{
  int count = 0;
  int len = strlen(str);
  int i;
  for (i = 1; i < len - 1; i++)
  {
    if (strchr("aeiou", str[i]) == ((void *)0))
    {
      if (strchr("aeiou", str[i - 1]) != ((void *)0) || strchr("aeiou", str[i + 1]) != ((void *)0))
      {
        count++;
      }
    }
  }
  if (strchr("aeiou", str[0]) == ((void *)0))
  {
    if (strchr("aeiou", str[1]) != ((void *)0))
    {
      count++;
    }
  }
  if (strchr("aeiou", str[len - 1]) == ((void *)0))
  {
    if (strchr("aeiou", str[len - 2]) != ((void *)0))
    {
      count++;
    }
  }
  return count;
}
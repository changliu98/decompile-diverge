char *strset(char *str, int c)
{
  char *s;

  for (s = str; *s != '\0'; s++)
    *s = c;
  return (str);
}
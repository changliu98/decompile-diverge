char *strset(char *str, int c)
{
  for (str = (char *)str; *str != '\0'; str++)
    *str = c;
  return (str);
}
void _uc(char *str)
{
  char *s = str;
  while (*s != '\0')
  {
    if (*s >= 'a' && *s <= 'z')
      *s -= 'a' - 'A';
    s++;
  }
}
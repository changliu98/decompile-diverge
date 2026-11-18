int unescape(char *str, char esc)
{
  char *dst = str;
  int count = 0;
  while (*str != esc && *str != '\0')
    str++;
  dst = str;
  while (*str != '\0')
  {
    if (*str == esc)
    {
      str++;
      count++;
    }
    *dst = *str;
    dst++;
    str++;
  }
  return count;
}
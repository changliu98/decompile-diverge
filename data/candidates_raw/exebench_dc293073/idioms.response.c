char *strtoupper(char *str)
{
  char *p = str;
  while (*p)
  {
    if (*p >= 'a' && *p <= 'z')
    {
      *p -= 'a' - 'A';
    }
    p++;
  }
  return str;
}
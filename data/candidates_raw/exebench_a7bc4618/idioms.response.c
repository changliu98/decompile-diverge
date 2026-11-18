void strchop(char *s, char c)
{
  char *p = strrchr(s, c);
  if (p)
    *p = '\0';
}
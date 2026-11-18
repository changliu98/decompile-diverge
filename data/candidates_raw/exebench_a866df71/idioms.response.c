char *strchri(char *s, char c)
{
  for (;;) {
    if (s[0] == c)
      return s;
    if (s[0] == '\0')
      return s;
    s++;
  }
}
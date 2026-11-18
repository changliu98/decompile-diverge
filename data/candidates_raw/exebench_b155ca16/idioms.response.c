char *strlit(char *s, char c)
{
  s[0] = c;
  s[1] = '\0';
  return s + 1;
}
void break_atr(char *s, char c)
{
  char *t = strrchr(s, c);
  if (t)
    *t = '\0';
}
void break_atr(char *str, char c)
{
  char *p;

  p = strrchr(str, c);
  if (p) {
    *p = 0;
  }
}
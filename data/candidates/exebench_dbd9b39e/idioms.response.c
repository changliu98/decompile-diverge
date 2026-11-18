void stress_chop(char *str, char ch)
{
  char *p = strchr(str, ch);
  if (p)
    *p = '\0';
}
char *strichr(char *s, int c)
{
  char *t;
  if (s) {
    for (t = s; *t; t++)
      ;
    for (t--; t >= s; t--)
      *(t + 1) = *t;
    *s = c;
  }
  return s;
}
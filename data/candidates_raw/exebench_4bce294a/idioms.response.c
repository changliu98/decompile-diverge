char *strins(char *s, int c)
{
  char *p;
  if (s) {
    for (p = s; *p; p++)
      continue;
    for (p--; p >= s; p--)
      *(p + 1) = *p;
    *s = c;
  }
  return s;
}
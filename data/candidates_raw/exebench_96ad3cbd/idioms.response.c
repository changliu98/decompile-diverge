char *getint(char *s, int *i)
{
  char *p = s;
  int n = 0;
  if (*p >= '0' && *p <= '9') {
    for (n = 0; ((('0') <= (*p)) && ((*p) <= ('9'))) ? 1 : 0; p++)
      n = n * 10 + *p - '0';
    *i = n;
  } else
    *i = 0;
  return p;
}
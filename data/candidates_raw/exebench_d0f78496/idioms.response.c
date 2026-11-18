char *getint(char *s, int nr, int *d)
{
  int n = 0;
  for ( ; --nr >= 0 && ((n = *s++) >= '0' && n <= '9'); n = n * 10 + (n - '0'));
  *d = n;
  return s;
}
char *int2str(int val, char *str, int base)
{
  int i;
  char *p;
  char *p1;
  char buf[32];
  char *p2;
  unsigned int uval;
  unsigned int uval1;
  memset(buf, 0, sizeof(buf));
  p = buf;
  p1 = str;
  if (base < 2 || base > 36)
  {
    *p1 = '\0';
    return p1;
  }
  i = val;
  uval = i;
  if (i < 0 && base == 10)
  {
    uval = -i;
  }
  do
  {
    *p++ = int2str_tab[uval % base];
    uval /= base;
  }
  while (uval);
  if (i < 0 && base == 10)
  {
    *p++ = '-';
  }
  p--;
  for ( ; ; p--)
  {
    int c = 0;
    if (p >= buf)
    {
      c = *p;
      *p1++ = *p;
      if (c == '\0')
      {
        break;
      }
    }
  }
  *p1 = '\0';
  return p1;
}
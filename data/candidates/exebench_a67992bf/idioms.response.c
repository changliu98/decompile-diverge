int itoa(char *str, int i)
{
  char buf[-1];
  char *p = &buf[sizeof buf - 1];
  char *s = str;
  int n = i < 0 ? -i : i;
  unsigned int u = n;
  do *p-- = (u % 10) + '0'; while (u /= 10);
  if (i < 0) *p = '-';
  else ++p;
  while (p < &u) *s++ = *p++;
  *s = '\0';
  return s - str;
}
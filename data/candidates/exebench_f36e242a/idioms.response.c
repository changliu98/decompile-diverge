int ltos(char *s, long n)
{
  char buf[16];
  char *t = buf;
  char *p = s;
  long long num;
  if (n < 0)
    num = -n;
  else
    num = n;
  for (num = n; num / 10 > 0; num /= 10)
    *t++ = (num % 10) + '0';
  if (n < 0)
    *p++ = '-';
  *p++ = (num % 10) + '0';
  while (t-- > buf)
    *p++ = *t;
  *p = '\0';
  return 0;
}
int itoa(char *str, int i)
{
  char buf[-1];
  char *p = buf + sizeof buf - 1;
  char *s = str;
  int n;
  if (i < 0)
    n = -i;
  else
    n = i;
  do
  {
    *p-- = n % 10 + '0';
    n /= 10;
  }
  while (n);
  if (i < 0)
    *p = '-';
  else
    ++p;
  while (p < buf + sizeof buf)
    *s++ = *p++;
  *s = '\0';
  return s - str;
}
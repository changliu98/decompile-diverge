int sdsull2str(char *str, unsigned long long n)
{
  char *s = str;
  char *p = str;
  char aux;
  int len;
  do
    {
      *p++ = n % 10 + '0';
      n /= 10;
    }
  while (n);
  len = p - s;
  *p = '\0';
  p--;
  for (s = str; s < p; s++)
    {
      aux = *s;
      *s = *p;
      *p = aux;
      p--;
    }
  return len;
}
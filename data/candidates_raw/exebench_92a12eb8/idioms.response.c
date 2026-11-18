void itoa(int n, char s[])
{
  char *t = s;
  char *p;
  int d;
  if (n < 0) {
    d = -n;
    *t = '-';
    t++;
  } else
    d = n;
  p = t;
  do {
    *p = d % 10 + '0';
    d /= 10;
    p++;
  } while (d != 0);
  *p = '\0';
  p--;
  while (t < --p) {
    d = *t;
    *t = *p;
    *p = d;
    t++;
  }
}
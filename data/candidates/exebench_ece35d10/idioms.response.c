char *itoa(int value, char *str, int radix)
{
  int i = value;
  char *s = str;
  int r = radix;
  char *d = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *p = s; char *h = s; char t;
  if (s == ((void *)0) || r < 2 || r > 36)
    return s;
  if (r != 10 && i < 0)
    return s;
  if (i == 0) {
    p = s + 1;
    *s = '0';
    *p = '\0';
    return p;
  }
  if (r == 10 && i < 0) {
    p = s + 1;
    *s = '-';
    i = -i;
  }
  while (i > 0) {
    *p++ = d[i % r];
    i /= r;
  }
  *p = '\0';
  for (p = p - 1; h < p; h++) {
    t = *h;
    *h = *p;
    *p = t;
    p--;
  }
  return s;
}
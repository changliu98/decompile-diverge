int util_read_dec(char *s, int *ip)
{
  int i; int sign;
  long n;
  char *p;
  p = s;
  sign = 0;
  i = 0;
  *ip = 0;
  if (*p == '-') {
    sign = 1;
    p++;
    i = 1;
  }
  n = 0;
  while (*p != '\0') {
    i = *p - '0';
    if (i > 9)
      break;
    n = n * 10 + i;
    if (n > 0x7fffffff)
      break;
    p++;
    i++;
  }
  if (sign) {
    if (i == 1)
      return 0;
    *ip = -*ip;
  }
  return i;
}
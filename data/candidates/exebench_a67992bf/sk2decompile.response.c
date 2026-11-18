int itoa(char *str, int num) {
  char *start = str;
  int n = num;
  char buf[12];
  char *p = buf + 11;
  char *q = str;
  unsigned int m = n < 0 ? -n : n;
  do {
    *p-- = '0' + m % 10;
    m /= 10;
  } while (m);
  if (n < 0)
    *p = '-';
  else
    p++;
  while (p < buf + 11) {
    *q++ = *p;
    p++;
  }
  *q = '\0';
  return q - start;
}
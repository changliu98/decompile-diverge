int itoa(char *str, int num) {
  char buf[12];
  char *start = str;
  char *p = buf + 11;
  char *q = str;
  unsigned int n = num < 0 ? -num : num;
  do {
    *p-- = '0' + n % 10;
    n /= 10;
  } while (n);
  if (num < 0)
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
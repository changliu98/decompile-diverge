int ltos(char *s, long l) {
  char buf[20];
  char *p = buf;
  unsigned long ul;
  if (l < 0)
    ul = -l;
  else
    ul = l;
  while (ul >= 10) {
    *p++ = '0' + ul % 10;
    ul /= 10;
  }
  if (l < 0) *s++ = '-';
  *s++ = '0' + ul;
  while (p-- > buf) *s++ = *p;
  *s = '\0';
  return 0;
}
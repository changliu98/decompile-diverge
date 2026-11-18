int sdsll2str(char *s, long long value) {
  unsigned long long v;
  char *p, *e, aux;
  int len;
  v = (value < 0) ? -value : value;
  p = s;
  do {
    *p++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  if (value < 0) *p++ = '-';
  len = p - s;
  *p = '\0';
  e = p - 1;
  while (s < e) {
    aux = *s;
    *s = *e;
    *e = aux;
    s++;
    e--;
  }
  return len;
}
int sdsll2str(char *s, long long value) {
  unsigned long long v;
  char *p, *e, aux;
  int len;
  p = s;
  if (value < 0) {
    if (value == (-9223372036854775807 - 1))
      v = (unsigned long long)(-9223372036854775807 - 1);
    else
      v = (unsigned long long)(-value);
  } else {
    v = (unsigned long long)value;
  }
  e = p;
  do {
    *e++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  if (value < 0) *e++ = '-';
  len = (int)(e - p);
  *e = '\0';
  e--;
  while (p < e) {
    aux = *p;
    *p = *e;
    *e = aux;
    p++;
    e--;
  }
  return len;
}
char *string_to_slong(char *str, long *val) {
  int c;
  int neg;
  char *p;
  p = str;
  c = *p;
  if (c == '-') {
    neg = 1;
    p++;
    c = *p;
  } else {
    neg = 0;
    if (c == '+') {
      p++;
      c = *p;
    }
  }
  *val = 0;
  while ((c >= '0') && (c <= '9')) {
    *val = *val * 10 + (c - '0');
    c = *++p;
  }
  if (neg) *val = -*val;
  return p;
}
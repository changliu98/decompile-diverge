char *ReadNumber(char *s, double *val) {
  double sign = 1.0;
  int i, j;
  double k;
  while (*s == '+' || *s == '-') {
    if (*s == '-') sign = -sign;
    s++;
  }
  i = 0;
  j = 0;
  k = 1.0;
  while (*s <= '9' && *s >= '0') {
    i = 10 * i + *s++ - '0';
  }
  if (*s == 0) {
    *val = sign * i;
    return s;
  }
  if (*s == '.') {
    s++;
    while (*s >= '0' && *s <= '9') {
      j = 10 * j + *s++ - '0';
      k *= 10.0;
    }
  }
  *val = sign * (i + j / k);
  return s;
}
int i_to_str(int i, char *s) {
  char *p, *q;
  int len, j;
  char c;
  q = s;
  if (i < 0) {
    *q++ = '-';
    i = -i;
  }
  p = q;
  do {
    *p++ = '0' + i % 10;
    i /= 10;
  } while (i);
  *p = '\0';
  len = p - q;
  for (j = 0; j < len / 2; j++) {
    c = q[j];
    q[j] = q[len - 1 - j];
    q[len - 1 - j] = c;
  }
  return p - s;
}
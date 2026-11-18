static int matchbrack(const char *brack, int c1, int c2) {
  const char *p = brack;
  int neg = 0;
  int c, c22;
  if (*p == '!' || *p == '^') {
    neg = 1;
    p++;
  }
  if (*p == ']') {
    if (c1 == ']') return !neg;
    p++;
  } else if (*p == '-') {
    if (c1 == '-') return !neg;
    p++;
  }
  c = *(p - 1);
  while (*p != ']') {
    if (*p == '-' && p[1] != ']') {
      p++;
      c22 = utf8get(&p);
      if (c <= c1 && c1 <= c22) return !neg;
      if (c <= c2 && c2 <= c22) return !neg;
    } else {
      c = utf8get(&p);
      if (c == c1 || c == c2) return !neg;
    }
  }
  return neg;
}
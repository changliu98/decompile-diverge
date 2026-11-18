static const char *parse_fmt(const char *fmt, int *v, int *len) {
  const char *p = fmt;
  do {
    while (*p && *p != '%') p++;
    if (*p == '%') {
      switch (p[1]) {
        case '%':
          *len = p - fmt + 1;
          *v = -1;
          return p + 2;
        case 'v':
          *v = 15;
          *len = p - fmt;
          return p + 2;
      }
    }
  } while (*p);
  *v = -1;
  *len = p - fmt;
  return p;
}
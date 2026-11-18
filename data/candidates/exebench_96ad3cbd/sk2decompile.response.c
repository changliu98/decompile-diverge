static char *maybeint(char *p, int *val) {
  int v;
  if (*p >= '0' && *p <= '9') {
    v = 0;
    while (*p >= '0' && *p <= '9') v = v * 10 + (*p++ - '0');
    *val = v;
  } else
    *val = 0;
  return p;
}
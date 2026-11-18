static const char *check_longlong_async_signal_safe(const char *p, int *ll) {
  *ll = 0;
  if (*p == 'l') {
    p++;
    if (*p == 'l') p++;
    *ll = 1;
  }
  return p;
}
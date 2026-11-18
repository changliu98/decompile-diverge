static const char *parse_content_length(const char *p, const char *e,
                                        int *len) {
  while (p < e && (*p == ' ' || *p == '\t' || (*p == '\r' && p[1] == '\n') ||
                   (*p == '\n' && (p[1] == ' ' || p[1] == '\t'))))
    p++;
  if (p == e) return NULL;
  int digits = 0;
  int n = 0;
  while (p < e && *p >= '0' && *p <= '9') {
    n = n * 10 + *p - '0';
    if (n < 0) return NULL;
    digits++;
    p++;
  }
  if (p == e || digits == 0) return NULL;
  while (p < e && (*p == ' ' || *p == '\t' || *p == '\n')) p++;
  if (p == e) return NULL;
  if (*p++ != '\n' && *p++ != '\r' || *p++ != '\n') return NULL;
  *len = n;
  return p;
}
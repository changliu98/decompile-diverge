sds sdscatrepr(sds s, const char *p, size_t len) {
  int c;
  s = sdscatlen(s, "\"", 1);
  while (len--) {
    c = *p;
    if (c == '\a') {
      s = sdscatlen(s, "\\a", 2);
    } else if (c == '\b') {
      s = sdscatlen(s, "\\b", 2);
    } else if (c == '\t') {
      s = sdscatlen(s, "\\t", 2);
    } else if (c == '\n') {
      s = sdscatlen(s, "\\n", 2);
    } else if (c == '\r') {
      s = sdscatlen(s, "\\r", 2);
    } else if (c == '"' || c == '\\') {
      s = sdscatprintf(s, "\\%c", c);
    } else if (isprint((unsigned char)c)) {
      s = sdscatprintf(s, "%c", c);
    } else {
      s = sdscatprintf(s, "\\x%02x", (unsigned char)c);
    }
    p++;
  }
  return sdscatlen(s, "\"", 1);
}
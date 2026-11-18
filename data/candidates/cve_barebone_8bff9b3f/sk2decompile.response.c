static const char *bittok2str_internal(const struct bittok *bittok,
                                       const char *unknown, unsigned int val,
                                       const char *sep) {
  static char buf[256];
  int len = 0;
  const char *prefix = "";
  unsigned int bit;
  while (bittok && bittok->str) {
    for (bit = 1; bit; bit <<= 1) {
      if ((bittok->val & bit) == bit) {
        len += snprintf(buf + len, sizeof(buf) - len, "%s%s", prefix,
                        bittok->str);
        prefix = sep;
        break;
      }
    }
    bittok++;
  }
  if (!len) {
    if (unknown)
      snprintf(buf, sizeof(buf), unknown, val);
    else
      snprintf(buf, sizeof(buf), "#%08x", val);
  }
  return buf;
}
bool wc_unescape(char *dest, const char *src) {
  while (*src) {
    if (*src == '\\') {
      src++;
      if (*src) {
        if (dest) *dest++ = *src;
        src++;
      }
    } else if (*src == '*' || *src == '?' || *src == '[' || *src == ']') {
      return false;
    } else {
      if (dest) *dest++ = *src;
      src++;
    }
  }
  if (dest) *dest = '\0';
  return true;
}
void xmlrpc_char_encode(char *dest, const char *src) {
  mowgli_string_t *str = mowgli_string_create();
  char buf[15];
  unsigned long i;
  unsigned char c;
  buf[0] = '\0';
  dest[0] = '\0';
  if (src == NULL || src[0] == '\0') return;
  for (i = 0; src[i] != '\0'; i++) {
    c = src[i];
    if (c > 127) {
      snprintf(buf, 15, "&#%d;", c);
      str->append(str, buf, strlen(buf));
    } else {
      switch (c) {
        case '&':
          str->append(str, "&amp;", 5);
          break;
        case '<':
          str->append(str, "&lt;", 4);
          break;
        case '>':
          str->append(str, "&gt;", 4);
          break;
        case '"':
          str->append(str, "&quot;", 6);
          break;
        default:
          str->append_c(str, c);
          break;
      }
    }
  }
  memcpy(dest, str->str, 4096);
}
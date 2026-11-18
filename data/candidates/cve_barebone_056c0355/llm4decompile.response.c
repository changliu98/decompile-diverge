void xmlrpc_char_encode(char *outbuffer, const char *s) {
  mowgli_string_t *str = mowgli_string_create();
  char buf[15];
  size_t i;

  buf[0] = '\0';
  outbuffer[0] = '\0';

  if (s == NULL || s[0] == '\0')
    return;

  for (i = 0; s[i] != '\0'; i++) {
    unsigned char c = (unsigned char)s[i];

    if (c > 127) {
      snprintf(buf, 15, "&#%d;", c);
      str->append(str, buf, strlen(buf));
    } else if (c == '&') {
      str->append(str, "&amp;", 5);
    } else if (c == '<') {
      str->append(str, "&lt;", 4);
    } else if (c == '>') {
      str->append(str, "&gt;", 4);
    } else if (c == '"') {
      str->append(str, "&quot;", 6);
    } else {
      str->append_char(str, c);
    }
  }

  memcpy(outbuffer, str->str, 4096);
}
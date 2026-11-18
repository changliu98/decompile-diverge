void Q_ParseNewlines(char *dest, const char *src, int destsize) {
  while (*src && destsize > 1) {
    char c;
    if (*src == '\\' && src[1] == 'n') {
      c = '\n';
      src++;
    } else {
      c = *src;
    }
    *dest++ = c;
    src++;
    destsize--;
  }
  *dest = 0;
}
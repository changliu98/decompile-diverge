char *i2hs(unsigned int i, char *s) {
  char *hex = "0123456789ABCDEF";
  char buf[32];
  char *p = buf;
  char *q = s;
  *p = 0;
  while (i) {
    *++p = hex[i & 0x0f];
    i >>= 4;
  }
  if (!*p) *++p = '0';
  while ((*q++ = *--p))
    ;
  return s;
}
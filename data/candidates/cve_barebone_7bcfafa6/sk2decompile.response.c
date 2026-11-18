char *url_canonize2(char *dst, const char *src, size_t dstlen, unsigned set1,
                    unsigned set2, unsigned set3, unsigned set4) {
  size_t i;
  char c, c1, c2, c3;
  char *d;
  d = dst;
  i = 0;
  if (dst == src) {
    while (src[i] && i < dstlen) {
      if (src[i] == '%') break;
      *d++ = src[i];
      i++;
    }
  }
  while (src[i] && i < dstlen) {
    c = src[i];
    if (c == '%') {
      c1 = src[i + 1];
      c2 = src[i + 2];
      if (!((c1 >= '0' && c1 <= '9') || (c1 >= 'A' && c1 <= 'F') ||
            (c1 >= 'a' && c1 <= 'f')) ||
          !((c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'F') ||
            (c2 >= 'a' && c2 <= 'f'))) {
        *d = 0;
        return NULL;
      }
      c3 = (((c1) >= 'a' ? (c1) - 'a' + 'A' : (c1)) - '0') * 16 +
           (((c2) >= 'a' ? (c2) - 'a' + 'A' : (c2)) - '0');
      if (c3 >= 0x21 && c3 <= 0x7e &&
          !((c3) < 0x40
                ? ((1 << ((c3)-0x21)) & (set1))
                : ((c3) < 0x60 ? ((1 << ((c3)-0x40)) & (set2))
                               : ((1 << ((c3)-0x60)) & (set3))))) {
        *d = c3;
        i += 2;
      } else {
        if ((c1) >= 'a') c1 = (c1) - 'a' + 'A';
        if ((c2) >= 'a') c2 = (c2) - 'a' + 'A';
        *d++ = '%';
        *d++ = c1;
        *d++ = c2;
        i += 2;
      }
    } else {
      if (!((1 << ((c)-0x21)) & (set1))) {
        if (c < 0x21 || c > 0x7e ||
            ((c) < 0x40 ? ((1 << ((c)-0x21)) & (set1))
                        : ((c) < 0x60 ? ((1 << ((c)-0x40)) & (set2))
                                      : ((1 << ((c)-0x60)) & (set3)))))
          return NULL;
      }
      *d = c;
    }
    d++;
    i++;
  }
  *d = 0;
  return d;
}
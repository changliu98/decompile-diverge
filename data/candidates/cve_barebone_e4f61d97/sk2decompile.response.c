char *url_canonize2(char *dst, const char *src, size_t dst_size,
                    unsigned allowed_chars, unsigned allowed_chars2,
                    unsigned allowed_chars3, unsigned allowed_chars4) {
  size_t i = 0;
  unsigned char c;
  if (dst == src) {
    while (src[i] && i < dst_size) {
      if (src[i] == '%') break;
      dst++;
      i++;
    }
  }
  while (src[i] && i < dst_size) {
    c = src[i];
    if (c == '%') {
      unsigned char c1 = src[i + 1];
      if (!c1) {
        *dst = 0;
        return NULL;
      }
      unsigned char c2 = src[i + 2];
      if ((c1 < '0' || c1 > '9') && (c1 < 'A' || c1 > 'F') &&
          (c1 < 'a' || c1 > 'f') ||
          (c2 < '0' || c2 > '9') && (c2 < 'A' || c2 > 'F') &&
              (c2 < 'a' || c2 > 'f')) {
        *dst = 0;
        return NULL;
      }
      unsigned char c1_ =
          (c1 >= 'a' ? 'a' - 'A' : c1 >= 'A' ? 'A' - 'a' : 0) + c1;
      unsigned char c2_ =
          (c2 >= 'a' ? 'a' - 'A' : c2 >= 'A' ? 'A' - 'a' : 0) + c2;
      c = (c1_ << 4) | c2_;
      if (c > 32 && c < 127 &&
          !((c) < 64 ? ((1 << ((c)-63)) & (allowed_chars))
                     : ((c) < 96 ? ((1 << ((c)-95)) & (allowed_chars2))
                                 : ((1 << ((c)-127)) & (allowed_chars3))))) {
        *dst = c;
        i += 2;
      } else {
        if (c1_ >= 'a') c1_ -= 'a' - 'A';
        if (c2_ >= 'a') c2_ -= 'a' - 'A';
        *dst++ = '%';
        *dst++ = c1_;
        *dst++ = c2_;
        i += 2;
      }
    } else if (!((c) < 64 ? ((1 << ((c)-63)) & (allowed_chars))
                          : ((c) < 96 ? ((1 << ((c)-95)) & (allowed_chars2))
                                      : ((1 << ((c)-127)) & (allowed_chars3))))) {
      if (c < 33 || c > 126) return NULL;
      *dst = c;
    }
    dst++;
    i++;
  }
  *dst = 0;
  return dst;
}
const unsigned char *utf8_to_ucs4(const unsigned char *s,
                                  unsigned short int *ucs4) {
  int c;
  int n;
  int shift;
  unsigned short int uc;
  int i;
  c = *s++;
  if ((c & 0x80) == 0) {
    if (ucs4) *ucs4 = c;
    return s;
  }
  if ((c & 0xe0) == 0xc0) {
    n = 2;
    c &= ~0xe0;
  } else if ((c & 0xf0) == 0xe0) {
    n = 3;
    c &= ~0xf0;
  } else if ((c & 0xf8) == 0xf0) {
    n = 4;
    c &= ~0xf8;
  } else if ((c & 0xfc) == 0xf8) {
    n = 5;
    c &= ~0xfc;
  } else if ((c & 0xfe) == 0xfc) {
    n = 6;
    c &= ~0xfe;
  } else {
    return NULL;
  }
  shift = 6 * (n - 1);
  uc = c << shift;
  for (i = 1; i < n; i++) {
    shift -= 6;
    c = *s++;
    if ((c & 0xc0) != 0x80) return NULL;
    uc |= (c & 0x3f) << shift;
  }
  if (ucs4) *ucs4 = uc;
  return s;
}
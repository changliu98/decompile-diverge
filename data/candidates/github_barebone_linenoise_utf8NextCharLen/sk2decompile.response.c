unsigned int utf8NextCharLen(const unsigned char *str, unsigned int start,
                             unsigned int len) {
  if (start >= len) return 0;
  unsigned long charLen = 0;
  unsigned int i = start;
  unsigned int c;
  unsigned int charLen1;
  int isFirstRI;
  c = utf8DecodeChar(str + i, &charLen1);
  charLen += charLen1;
  i += charLen1;
  isFirstRI = isRegionalIndicator(c);
  while (i < len) {
    unsigned int c2;
    unsigned int charLen2;
    c2 = utf8DecodeChar(str + i, &charLen2);
    if (isZWJ(c2) && i + charLen2 < len) {
      charLen += charLen2;
      i += charLen2;
      utf8DecodeChar(str + i, &charLen2);
      charLen += charLen2;
      i += charLen2;
    } else if (isGraphemeExtend(c2)) {
      charLen += charLen2;
      i += charLen2;
    } else if (isFirstRI && isRegionalIndicator(c2)) {
      charLen += charLen2;
      i += charLen2;
      isFirstRI = 0;
    } else {
      return charLen;
    }
  }
  return charLen;
}
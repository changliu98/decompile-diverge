size_t utf8NextCharLen(char *string, size_t start, size_t end) {
  size_t length;
  if (start >= end) {
    length = 0;
  } else {
    size_t pos, total;
    bool lastWasRI;
    unsigned int codepoint, nextCodepoint;
    size_t nextLen;

    total = 0;
    pos = start;

    codepoint = utf8DecodeChar(string + pos, &nextLen);
    total += nextLen;
    pos += nextLen;
    lastWasRI = isRegionalIndicator(codepoint);

    while (true) {
      if (pos >= end) {
        break;
      }

      nextCodepoint = utf8DecodeChar(string + pos, &nextLen);

      if (isZWJ(nextCodepoint) && pos + nextLen < end) {

        total += nextLen;
        pos += nextLen;
        nextCodepoint = utf8DecodeChar(string + pos, &nextLen);
        total += nextLen;
        pos += nextLen;
      } else if (isGraphemeExtend(nextCodepoint)) {

        total += nextLen;
        pos += nextLen;
      } else if (lastWasRI && isRegionalIndicator(nextCodepoint)) {

        total += nextLen;
        pos += nextLen;
        lastWasRI = false;
      } else {

        break;
      }
    }

    length = total;
  }

  return length;
}
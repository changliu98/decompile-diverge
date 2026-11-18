static int defaultPrevCharLen(const unsigned char *z, int n, int pos,
                              size_t *pLen) {
  if (pLen) {
    *pLen = 1;
  }
  return 1;
}
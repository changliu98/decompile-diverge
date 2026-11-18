unsigned fnv_32a_buf(void *buf, size_t len, unsigned hval) {
  unsigned char *bp;
  unsigned char *be;
  bp = (unsigned char *)buf;
  be = bp + len;
  while (bp < be) {
    hval ^= (unsigned)*bp++;
    hval +=
        (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
  }
  return hval;
}
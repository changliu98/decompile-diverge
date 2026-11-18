unsigned fnv_32_buf(void *buf, size_t len, unsigned hval) {
  unsigned char *bp;
  unsigned char *be;
  bp = (unsigned char *)buf;
  be = bp + len;
  while (bp < be) {
    hval *= ((unsigned)0x01000193);
    hval ^= (unsigned)*bp++;
  }
  return hval;
}
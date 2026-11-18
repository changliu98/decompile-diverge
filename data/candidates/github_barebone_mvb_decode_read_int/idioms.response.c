int read_int(void *src, char *dst)
{
  unsigned char *s = (const u_char *)src;
  unsigned int n = (uint32_t) *s++ & 0x7f;
  if (n < 0x80) {
    snprintf(dst, 10, "%d", n);
  } else {
    n &= 0x7f;
    n |= (unsigned int) *s++ << 7;
    if (n < 0x8000) {
      snprintf(dst, 10, "%d", n);
    } else {
      n &= 0x7f;
      n |= (unsigned int) *s++ << 14;
      if (n < 0x800000) {
        snprintf(dst, 10, "%d", n);
      } else {
        n &= 0x7f;
        n |= (unsigned int) *s++ << 21;
        if (n < 0x8000000) {
          snprintf(dst, 10, "%d", n);
        } else {
          n &= 0x7f;
          n |= (unsigned int) *s++ << 28;
          snprintf(dst, 10, "%d", n);
        }
      }
    }
  }
  return 10 - strlen(dst);
}
static inline Fnv32_t fnv_32_buf(void *buf, unsigned long len, Fnv32_t hval)
{
  unsigned char *bp = (const unsigned char *)buf;
  for ( ; bp < (const unsigned char *)((char *)buf + len); ++bp )
    hval = (hval * 16777619) ^ (unsigned int)(*bp);
  return hval;
}
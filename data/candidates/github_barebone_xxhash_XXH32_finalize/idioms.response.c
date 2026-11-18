unsigned int XXH32_finalize(void *input, unsigned long len, unsigned int seed)
{
  unsigned int h32 = seed;
  unsigned char *data = (const unsigned char *)input;
  unsigned int *d32 = (const unsigned int *)data;
  len &= ~((sizeof(unsigned int)) - 1);
  while (len >= sizeof(unsigned int))
  {
    h32 += XXH_readLE32(d32);
    d32++;
    h32 = (h32 << 17) | (h32 >> (32 - 17));
    h32 *= 668265263U;
    len -= sizeof(unsigned int);
  }
  data = (unsigned char *)d32;
  while (len)
  {
    h32 += *data;
    h32 = (h32 << 11) | (h32 >> (32 - 11));
    h32 *= 374761393U;
    data++;
    len--;
  }
  return XXH32_memory(h32);
}
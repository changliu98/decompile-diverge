void *memchr2(void *src, int c1, int c2, unsigned long n)
{
  unsigned char *s = (const unsigned char *)src;
  if (c1 == c2)
    return memchr(src, c1, n);
  if (n > 0 && (unsigned char)c1 == (unsigned char)c2)
    return memchr(src, c1, n);
  if (n > 0 && (unsigned char)c1 != (unsigned char)c2)
  {
    unsigned long i = n;
    unsigned long long repeated_c1 = (uint64_t)(uint32_t)c1 | ((uint64_t)(uint32_t)c1 << 32);
    unsigned long long repeated_c2 = (uint64_t)(uint32_t)c2 | ((uint64_t)(uint32_t)c2 << 32);
    unsigned long long repeated_c1a = (uint64_t)(uint32_t)c1 | ((uint64_t)(uint32_t)c1 << 16);
    unsigned long long repeated_c2a = (uint64_t)(uint32_t)c2 | ((uint64_t)(uint32_t)c2 << 16);
    unsigned long long *l = (const uint64_t *)s;
    while (i >= 8
           && !((repeated_c1 ^ *l) & ((repeated_c1 ^ *l) - 0x101010101010101ul) & 0x8080808080808080ul)
           && !((repeated_c2 ^ *l) & ((repeated_c2 ^ *l) - 0x101010101010101ul) & 0x8080808080808080ul))
    {
      l++;
      i -= 8;
    }
    s = (unsigned char *)l;
    while (i > 0)
    {
      if (*s == c1 || *s == c2)
        return s;
      i--;
      s++;
    }
  }
  return ((void *)0);
}
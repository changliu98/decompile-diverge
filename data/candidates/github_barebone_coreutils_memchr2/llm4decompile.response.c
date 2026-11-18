void *memchr2 (const void *s, int c1, int c2, size_t n)
{
  const unsigned char *s1 = (const unsigned char *) s;
  unsigned char u1 = (unsigned char) c1;
  unsigned char u2 = (unsigned char) c2;

  if (u1 == u2)
    return (void *) memchr (s, u1, n);


  for (; ((--n) & (sizeof (size_t) - 1)) && (*s1 != u1) && (*s1 != u2); s1++);

  if (n == 0)
    return NULL;


  size_t *w;
  size_t k = ((size_t) u1 << (sizeof (size_t) * 8 - 8)) | u1;
  size_t l = ((size_t) u2 << (sizeof (size_t) * 8 - 8)) | u2;

  for (w = (void *) s1;
       n >= (sizeof (size_t)) && !((*w ^ k) - (((size_t) -1) / 0xff) & ~(*w ^ k) & (((size_t) -1) / 0x80) * 0x80) && !((*w ^ l) - (((size_t) -1) / 0xff) & ~(*w ^ l) & (((size_t) -1) / 0x80) * 0x80);
       w++, n -= (sizeof (size_t)));


  for (s1 = (const unsigned char *) w; n; n--, s1++)
    if (*s1 == u1 || *s1 == u2)
      return (void *) s1;

  return NULL;
}
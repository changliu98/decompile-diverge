static unsigned long wyrand(void *key, unsigned long len, unsigned long seed, void *secret)
{
  unsigned long a; unsigned long b;
  unsigned long *s = (const uint64_t *)key;
  unsigned long l = len;
  unsigned long *se = (const uint64_t *)secret;
  unsigned char *p = (const uint8_t *)key;
  unsigned long s1 = seed ^ wymix((se[0]) ^ seed, se[1]);
  if (len < 16) {
    if (len < 4) {
      if (len == 0)
        a = b = 0;
      else {
        a = wyr3(p, len);
        b = 0;
      }
    }
    else {
      unsigned long h = wyr4(p);
      unsigned long h2 = wyr4(p + (len >> 3)*4);
      a = h | (h2 << 32);
      h = wyr4(p + len - 4);
      h2 = wyr4(p + len - 4 - (len >> 3)*4);
      b = h | (h2 << 32);
    }
  }
  else {
    unsigned long l = len;
    if (len >= 48) {
      unsigned long s2 = s1;
      unsigned long s3 = s1;
      do {
        unsigned long h = (se[1]) ^ wyr8(p);
        s1 = wymix((se[0]) ^ wyr8(p + 8), s1 ^ h);
        h = (se[2]) ^ wyr8(p + 16);
        s2 = wymix((se[1]) ^ wyr8(p + 24), s2 ^ h);
        h = (se[3]) ^ wyr8(p + 32);
        s3 = wymix((se[2]) ^ wyr8(p + 40), s3 ^ h);
        p += 48;
        l -= 48;
      } while (l >= 48);
      s1 ^= s2 ^ s3;
    }
    while (l >= 16) {
      unsigned long h = (se[1]) ^ wyr8(p);
      s1 = wymix((se[0]) ^ wyr8(p + 8), s1 ^ h);
      l -= 16;
      p += 16;
    }
    a = wyr8(p + l - 16);
    b = wyr8(p + l - 8);
  }
  a ^= (se[1]);
  b ^= s1;
  wymum(&a, &b);
  return wymix((se[0]) ^ (se[1]) ^ a ^ l, b ^ (se[1]));
}
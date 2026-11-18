void MurmurHash3_x86_32(const void *key, int len, unsigned int seed,
                        unsigned int *out) {
  const unsigned int c1 = 0xcc9e2d51;
  const unsigned int c2 = 0x1b873593;
  const unsigned int r1 = 15;
  const unsigned int r2 = 13;
  const unsigned int m = 5;
  const unsigned int *data = (const unsigned int *)key;
  const unsigned int *end = data + len / 4;
  const unsigned char *data2 = (const unsigned char *)end;
  unsigned int h1 = seed;
  unsigned int h2 = 0;
  unsigned int k1;
  int i;
  for (i = -len / 4; i; i++) {
    k1 = data[i];
    k1 *= c1;
    k1 = (k1 << r2) | (k1 >> (32 - r2));
    k1 *= c2;
    h1 ^= k1;
    h1 = ((h1 << m) | (h1 >> (32 - m)));
    h1 += c2;
    h1 = h1 << 10 | h1 >> (32 - 10);
  }
  k1 = 0;
  switch (len & 3) {
    case 3:
      k1 ^= data2[2] << 16;
    case 2:
      k1 ^= data2[1] << 8;
    case 1:
      k1 ^= data2[0];
      k1 *= c1;
      k1 = (k1 << r2) | (k1 >> (32 - r2));
      k1 *= c2;
      h2 ^= k1;
  }
  h2 ^= len;
  h2 ^= h2 >> 16;
  h2 *= 0x85ebca6b;
  h2 ^= h2 >> 13;
  h2 *= 0xc2b2ae35;
  h2 ^= h2 >> 16;
  *out = h2;
}
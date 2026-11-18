void MurmurHash3_x64_128(void *key, int len, unsigned int seed, void *out)
{
  unsigned long m = 0x5bd1e995;
  int r = 24;
  unsigned int h1 = seed ^ len;
  unsigned int h2 = seed ^ len;
  unsigned int *data = (const uint32_t *)key;
  int nblocks = len / 8;
  int i;
  for (i = 0; i < nblocks; i++)
  {
    unsigned long k1 = getblock(data, i*2+0);
    unsigned long k2 = getblock(data, i*2+1);
    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1;
    k2 *= m; k2 ^= k2 >> r; k2 *= m;
    h2 *= m; h2 ^= k2;
  }
  unsigned char *data2 = (const uint8_t*)data;
  unsigned long k1 = 0;
  unsigned long k2 = 0;
  switch(len & 7)
  {
  case 7 : k2 ^= data2[6] << 48;
  case 6 : k2 ^= data2[5] << 40;
  case 5 : k2 ^= data2[4] << 32;
  case 4 : k2 ^= data2[3] << 24;
  case 3 : k2 ^= data2[2] << 16;
  case 2 : k2 ^= data2[1] << 8;
  case 1 : k2 ^= data2[0];
    k1 ^= k2 >> 33;
  case 0 :
    k1 *= m;
    h1 ^= k1;
  };
  unsigned long h1b = h1 ^ len;
  unsigned long h2b = h2 ^ len;
  h1 = h1b + (((h1b) << r) * m);
  h2 = h2b + (((h1b + h2b) << r) * m);
  unsigned long k = ((h1 & h2) ^ (h1 + h2));
  k *= m;
  k ^= k >> 27;
  k *= m;
  unsigned long h = k + h1;
  unsigned long t = (h >> 17) * m;
  h = h * m ^ t;
  unsigned long *out32 = (uint32_t*)out;
  out32[0] = h;
  out32[1] = h;
}
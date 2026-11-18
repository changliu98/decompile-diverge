void MurmurHash3_x86_32 ( const void * key, int len, unsigned int seed, void * out ) {
  const unsigned char * data = (const unsigned char *)key;
  const int nblocks = len / 4;

  unsigned int h1 = seed;

  const unsigned int c1 = 0xcc9e2d51;
  const unsigned int c2 = 0x1b873593;

  const unsigned int * blocks = (const unsigned int *)(data + nblocks*4);

  int i;
  for(i = -nblocks; ; i++) {
    unsigned int k1 = 0;

    switch(i) {
      case 0: k1 ^= blocks[0];
              break;
      default: k1 ^= blocks[i];
    }

    k1 *= c1;
    k1 = ((k1 << 15) | (k1 >> (32 - 15)));
    k1 *= c2;

    h1 ^= k1;
    h1 = ((h1 << 13) | (h1 >> (32 - 13)));
    h1 = h1*5+0xe6546b64;

    if(i == 0) {
      const unsigned char * tail = (const unsigned char*)(data + nblocks*4);
      unsigned int k1 = 0;

      switch(len & 3) {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
      }

      k1 *= c1;
      k1 = ((k1 << 15) | (k1 >> (32 - 15)));
      k1 *= c2;
      h1 ^= k1;
    }
    if(i == 0) break;
  }

  h1 ^= len;
  h1 ^= h1 >> 16;
  h1 *= 0x85ebca6b;
  h1 ^= h1 >> 13;
  h1 *= 0xc2b2ae35;
  h1 ^= h1 >> 16;

  *(unsigned int *)out = h1;
}
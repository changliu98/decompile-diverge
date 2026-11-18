void MurmurHash3_x86_32(void *key, int len, unsigned int seed, void *out)
{
  unsigned int m = 0x5bd1e995;
  int r = 24;
  unsigned int h = seed ^ len;
  unsigned int *data = (const unsigned int *)key;
  int i = len/4;
  while( i-- )
  {
    unsigned int k = *data++;
    k *= m;
    k ^= k >> r;
    k *= m;
    h *= m;
    h ^= k;
  }
  unsigned char *data2 = (const unsigned char*)data;
  unsigned int k = 0;
  switch( len & 3 )
  {
    case 3: k ^= data2[2] << 16;
    case 2: k ^= data2[1] << 8;
    case 1: k ^= data2[0];
      k *= m;
  };
  h ^= k;
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  unsigned int *out32 = (unsigned int *)out;
  *out32 = h;
}
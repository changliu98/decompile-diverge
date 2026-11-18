void MurmurHash3_x86_128(void *key, int len, unsigned int seed, void *out)
{
  unsigned int m = 0x5bd1e995;
  int r = 24;
  unsigned int h1 = seed ^ len;
  unsigned int h2 = seed ^ len;
  unsigned int h3 = seed ^ len;
  unsigned int h4 = seed ^ len;
  unsigned int *data = (const uint32_t *)key;
  int nblocks = len / 16;
  int i;
  for (i = 0; i < nblocks; i++)
  {
    unsigned int k1 = data[i*4+0];
    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1 ;
    unsigned int k2 = data[i*4+1];
    k2 *= m; k2 ^= k2 >> r; k2 *= m;
    h2 *= m; h2 ^= k2 ;
    unsigned int k3 = data[i*4+2];
    k3 *= m; k3 ^= k3 >> r; k3 *= m;
    h3 *= m; h3 ^= k3 ;
    unsigned int k4 = data[i*4+3];
    k4 *= m; k4 ^= k4 >> r; k4 *= m;
    h4 *= m; h4 ^= k4 ;
  }
  unsigned char *data2 = (const uint8_t *)key;
  unsigned int k1 = 0;
  unsigned int k2 = 0;
  unsigned int k3 = 0;
  unsigned int k4 = 0;
  switch(len & 15)
  {
    case 15: k4 ^= data2[14] << 16;
    case 14: k4 ^= data2[13] << 8;
    case 13: k4 ^= data2[12];
            h4 *= m; h4 ^= k4 ;
    case 12: k3 ^= data2[11] << 24;
    case 11: k3 ^= data2[10] << 16;
    case 10: k3 ^= data2[ 9] << 8;
    case 9 : k3 ^= data2[ 8];
            h3 *= m; h3 ^= k3 ;
    case 8 : k2 ^= data2[ 7] << 24;
    case 7 : k2 ^= data2[ 6] << 16;
    case 6 : k2 ^= data2[ 5] << 8;
    case 5 : k2 ^= data2[ 4];
            h2 *= m; h2 ^= k2 ;
    case 4 : k1 ^= data2[ 3] << 24;
    case 3 : k1 ^= data2[ 2] << 16;
    case 2 : k1 ^= data2[ 1] << 8;
    case 1 : k1 ^= data2[ 0];
            h1 *= m; h1 ^= k1 ;
  };
  h2 ^= len;
  h3 ^= len;
  h4 ^= len;
  h1 += h2;
  h1 += h3;
  h1 += h4;
  unsigned int k = h1;
  k ^= k >> 13;
  k *= m;
  k ^= k >> 15;
  unsigned int h1b = h1 ^ k;
  unsigned int h2b = h2 ^ k;
  unsigned int h3b = h3 ^ k;
  unsigned int h4b = h4 ^ k;
  h1 = h1b;
  h1 += h2b;
  h1 += h3b;
  h1 += h4b;
  unsigned int k1b = h1;
  k1b ^= k1b >> 13;
  k1b *= m;
  k1b ^= k1b >> 15;
  unsigned int h1c = h1 ^ k1b;
  unsigned int h2c = h2b + h1c;
  unsigned int h3c = h3b + h1c;
  unsigned int h4c = h4b + h1
void MurmurHash3_x86_128(const void *key, int len, unsigned int seed,
                         unsigned int *out) {
  const unsigned int c1 = 0xcc9e2d51;
  const unsigned int c2 = 0x1b873593;
  const unsigned int c3 = 0x654e3b2d;
  const unsigned int c4 = 0x85ebca6b;
  const unsigned int c5 = 0xc2b2ae35;
  const unsigned int c6 = 0x27d4eb2f;
  const int nblocks = 16;
  const int nblocks_ = len / nblocks;
  const unsigned int *blocks = (const unsigned int *)key;
  const unsigned int *tail = blocks + nblocks_;
  unsigned int h1 = seed;
  unsigned int h2 = seed;
  unsigned int h3 = seed;
  unsigned int h4 = seed;
  unsigned int k1;
  int i;
  for (i = -nblocks_; i; i++) {
    k1 = tail[i * 4];
    h1 = h1 ^ k1 * c1;
    h1 = (((h1) << (13)) | ((h1) >> (32 - (13))));
    h1 = h1 * c2 + c6;
    k1 = tail[i * 4 + 1];
    h2 = h2 ^ k1 * c3;
    h2 = (((h2) << (16)) | ((h2) >> (32 - (16))));
    h2 = h2 * c4 + c5;
    k1 = tail[i * 4 + 2];
    h3 = h3 ^ k1 * c1;
    h3 = (((h3) << (13)) | ((h3) >> (32 - (13))));
    h3 = h3 * c2 + c6;
    k1 = tail[i * 4 + 3];
    h4 = h4 ^ k1 * c3;
    h4 = (((h4) << (16)) | ((h4) >> (32 - (16))));
    h4 = h4 * c4 + c5;
  }
  const unsigned char *tail_ = (const unsigned char *)key;
  const unsigned char *tail_2 = tail_ + nblocks_ * nblocks;
  unsigned int k2 = 0;
  switch (len % nblocks) {
    case 15:
      k2 ^= (unsigned int)(tail_2[14]) << 16;
    case 14:
      k2 ^= (unsigned int)(tail_2[13]) << 8;
    case 13:
      k2 ^= (unsigned int)(tail_2[12]) << 0;
      h4 ^= k2 * c1;
      h4 = (((h4) << (13)) | ((h4) >> (32 - (13))));
      h4 = h4 * c2 + c6;
    case 12:
      k2 ^= (unsigned int)(tail_2[11]) << 24;
    case 11:
      k2 ^= (unsigned int)(tail_2[10]) << 16;
    case 10:
      k2 ^= (unsigned int)(tail_2[9]) << 8;
    case 9:
      k2 ^= (unsigned int)(tail_2[8]) << 0;
      h3 ^= k2 * c3;
      h3 = (((h3) << (16)) | ((h3) >> (32 - (16))));
      h3 = h3 * c4 + c5;
    case 8:
      k2 ^= (unsigned int)(tail_2[7]) << 24;
    case 7:
      k2 ^= (unsigned int)(tail_2[6]) << 16;
    case 6:
      k2 ^= (unsigned int)(tail_2[5]) << 8;
    case 5:
      k2 ^= (unsigned int)(tail_2[4]) << 0;
      h2 ^= k2 * c1;
      h2 = (((h2) << (13)) | ((h2) >> (32 - (13))));
      h2 = h2 * c2 + c6;
    case 4:
      k2 ^= (unsigned int)(tail_2[3]) << 24;
    case 3:
      k2 ^= (unsigned int)(tail_2[2]) << 16;
    case 2:
      k2 ^= (unsigned int)(tail_2[1]) << 8;
    case 1:
      k2 ^= (unsigned int)(tail_2[0]) << 0;
      h1 ^= k2 * c1;
      h1 = (((h1) << (13)) | ((h1) >> (32 - (13))));
      h1 = h1 * c2 + c6;
  }
  h1 ^= len;
  h2 ^= len;
  h3 ^= len;
  h4 ^= len;
  h1 += h2;
  h1 += h3;
  h1 += h4;
  h2 += h1;
  h3 += h1;
  h4 += h1;
  h1 ^= h2;
  h1 ^= h1 >> 16;
  h1 *= 0x85ebca6b;
  h1 ^= h1 >> 13;
  h1 *= 0xc2b2ae35;
  h1 ^= h1 >> 16;
  h2 ^= h3;
  h2 ^= h2 >> 13;
  h2 *= 0x27d4eb2f;
  h2 ^= h2 >> 16;
  h3 ^= h4;
  h3 ^= h3 >> 13;
  h3 *= 0x654e3b2d;
  h3 ^= h3 >> 16;
  h4 ^= h1;
  h4 ^= h4 >> 13;
  h4 *= 0x85ebca6b;
  h4 ^= h4 >> 16;
  out[0] = h1;
  out[1] = h2;
  out[2] = h3;
  out[3] = h4;
}
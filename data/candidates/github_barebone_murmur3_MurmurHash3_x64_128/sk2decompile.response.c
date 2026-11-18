void MurmurHash3_x64_128(const void *key, int len, unsigned int seed,
                         unsigned int *out) {
  const unsigned int c1 = 0x5bd1e995;
  const unsigned int c2 = 0x55555555;
  const int r1 = 24;
  unsigned int h1 = seed;
  unsigned int h2 = seed;
  unsigned int len2 = len;
  const unsigned int *data = (const unsigned int *)key;
  const unsigned int *end = data + len / 16;
  unsigned int k1, k2, i;
  unsigned int h1_1, h2_1;
  int j;
  i = len & 15;
  k2 = len;
  k1 = len;
  h1_1 = h1;
  h2_1 = h2;
  for (j = 0; j < k2; j += 16) {
    h1_1 ^= data[j + 0];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 1];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 2];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 3];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 4];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 5];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 6];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 7];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 8];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 9];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 10];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 11];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 12];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 13];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 14];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h1_1 ^= data[j + 15];
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h1_1 += c1;
    h2_1 ^= h1_1;
    h2_1 = (((h2_1) << (r1)) | ((h2_1) >> (64 - (r1))));
    h2_1 += c2;
    h1_1 ^= h2_1;
    h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
    h2_1 += c2;
  }
  end = data + k2;
  k1 = 0;
  h1_1 = 0;
  h2_1 = 0;
  switch (i) {
    case 15:
      k1 ^= end[14] << 48;
    case 14:
      k1 ^= end[13] << 40;
    case 13:
      k1 ^= end[12] << 32;
    case 12:
      k1 ^= end[11] << 24;
    case 11:
      k1 ^= end[10] << 16;
    case 10:
      k1 ^= end[9] << 8;
    case 9:
      k1 ^= end[8] << 0;
      k1 *= c1;
      k1 = (((k1) << (r1)) | ((k1) >> (64 - (r1))));
      k1 *= c1;
      h1_1 ^= k1;
    case 8:
      k1 = 0;
    case 7:
      k1 ^= end[7] << 56;
    case 6:
      k1 ^= end[6] << 48;
    case 5:
      k1 ^= end[5] << 40;
    case 4:
      k1 ^= end[4] << 32;
    case 3:
      k1 ^= end[3] << 24;
    case 2:
      k1 ^= end[2] << 16;
    case 1:
      k1 ^= end[1] << 8;
    case 0:
      k1 ^= end[0] << 0;
      k1 *= c1;
      k1 = (((k1) << (r1)) | ((k1) >> (64 - (r1))));
      k1 *= c1;
      h1_1 ^= k1;
  };
  h1_1 ^= len2;
  h2_1 ^= len2;
  h1_1 += h2_1;
  h2_1 += h1_1;
  h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
  h1_1 *= c1;
  h1_1 ^= h2_1;
  h1_1 = (((h1_1) << (r1)) | ((h1_1) >> (64 - (r1))));
  h1_1 *= c1;
  h2_1 = (((h2_1) << (r1)) | ((h2_1) >> (64 - (r1))));
  h2_1 *= c1;
  h2_1 ^= h1_1;
  h2_1 = (((h2_1) << (r1)) | ((h2_1) >> (64 - (r1))));
  h2_1 *= c1;
  h2_1 ^= len2;
  out[0] = h1_1;
  out[1] = h2_1;
}
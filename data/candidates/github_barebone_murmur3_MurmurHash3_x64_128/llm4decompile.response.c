void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out)
{
 const uint64_t c1 = 0x87c37b91114253d5ULL;
 const uint64_t c2 = 0x4cf5ad432745937fULL;
 const int nblocks = len / 16;

 uint64_t h1 = seed ^ (c1 * (len * c2));
 uint64_t h2 = c2 * (len * c1);

 const uint64_t *blocks = (const uint64_t *)key;

 for (int i = 0; i < nblocks; i++) {
  uint64_t k1 = blocks[2 * i];
  uint64_t k2 = blocks[2 * i + 1];

  k1 *= c1;
  k1 = (((k1) << (31)) | ((k1) >> (64 - (31)))) * c2;
  h1 ^= k1;

  h1 = (((h1) << (27)) | ((h1) >> (64 - (27)))) * c1 + c2;

  k2 *= c2;
  k2 = (((k2) << (33)) | ((k2) >> (64 - (33)))) * c1;
  h2 ^= k2;

  h2 = (((h2) << (29)) | ((h2) >> (64 - (29)))) * c2 + c1;
 }

 uint64_t k1 = 0;
 uint64_t k2 = 0;

 const unsigned char *tail = (const unsigned char *)key + nblocks * 16;

 switch (len & 15) {
 case 15:
  k2 ^= ((uint64_t)tail[14]) << 48;

 case 14:
  k2 ^= ((uint64_t)tail[13]) << 40;

 case 13:
  k2 ^= ((uint64_t)tail[12]) << 32;

 case 12:
  k2 ^= ((uint64_t)tail[11]) << 24;

 case 11:
  k2 ^= ((uint64_t)tail[10]) << 16;

 case 10:
  k2 ^= ((uint64_t)tail[9]) << 8;

 case 9:
  k2 ^= ((uint64_t)tail[8]);
  k2 *= c2;
  k2 = (((k2) << (33)) | ((k2) >> (64 - (33)))) * c1;
  h2 ^= k2;

 case 8:
  k1 ^= ((uint64_t)tail[7]) << 56;

 case 7:
  k1 ^= ((uint64_t)tail[6]) << 48;

 case 6:
  k1 ^= ((uint64_t)tail[5]) << 40;

 case 5:
  k1 ^= ((uint64_t)tail[4]) << 32;

 case 4:
  k1 ^= ((uint64_t)tail[3]) << 24;

 case 3:
  k1 ^= ((uint64_t)tail[2]) << 16;

 case 2:
  k1 ^= ((uint64_t)tail[1]) << 8;

 case 1:
  k1 ^= ((uint64_t)tail[0]);
  k1 *= c1;
  k1 = (((k1) << (31)) | ((k1) >> (64 - (31)))) * c2;
  h1 ^= k1;

 }

 uint64_t *out64 = (uint64_t *)out;

 uint64_t out1 = h1 ^ (len * c1);
 out1 = (((out1) << (27)) | ((out1) >> (64 - (27)))) * c1 + c2;
 out1 = (((out1) << (21)) | ((out1) >> (64 - (21)))) * c2;

 uint64_t out2 = h2 ^ (len * c2);
 out2 = (((out2) << (29)) | ((out2) >> (64 - (29)))) * c2 + c1;
 out2 = (((out2) << (21)) | ((out2) >> (64 - (21)))) * c1;

 out64[0] = out1 + out2;
 out64[1] = out2 + out1;
}
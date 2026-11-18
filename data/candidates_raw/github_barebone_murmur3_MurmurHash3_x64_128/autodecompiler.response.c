void MurmurHash_x64_128_v3(const void *key, const int len, const uint32_t seed, void *out) {
 const unsigned char * data = (const unsigned char *)key;
 const int nblocks = len / 16;

 uint64_t h1 = seed;
 uint64_t h2 = seed;

 uint64_t c1 = 0x87c37b91114253d5ULL;
 uint64_t c2 = 0x4cf5ad432745937fULL;

 const uint64_t * blocks = (const uint64_t *)(data + nblocks * 16);

 uint64_t k1, k2, k3, k4;
 int i;

 for (i = 0; i < nblocks; i++) {
  k1 = blocks[i * 2];
  k2 = blocks[i * 2 + 1];

  k1 *= c1; k1 = ((k1 << 31) | (k1 >> (64 - 31))); k1 *= c2; h1 ^= k1;
  h1 = ((h1 << 27) | (h1 >> (64 - 27))); h1 += h2;
  h1 = h1 * 5 + 0x52dce729ULL;

  k2 *= c2; k2 = ((k2 << 33) | (k2 >> (64 - 33))); k2 *= c1; h2 ^= k2;
  h2 = ((h2 << 31) | (h2 >> (64 - 31))); h2 += h1;
  h2 = h2 * 5 + 0x38495ab5ULL;
 }

 const unsigned char * tail = (const unsigned char*)(data + nblocks * 16);
 uint64_t k3 = 0, k4 = 0;

 switch (len & 15) {
 case 15: k4 ^= ((uint64_t)tail[14]) << 56;
 case 14: k4 ^= ((uint64_t)tail[13]) << 48;
 case 13: k4 ^= ((uint64_t)tail[12]) << 40;
 case 12: k4 ^= ((uint64_t)tail[11]) << 32;
 case 11: k4 ^= ((uint64_t)tail[10]) << 24;
 case 10: k4 ^= ((uint64_t)tail[9]) << 16;
 case 9: k4 ^= ((uint64_t)tail[8]) << 8;

 case 8: k3 ^= ((uint64_t)tail[7]) << 56;
 case 7: k3 ^= ((uint64_t)tail[6]) << 48;
 case 6: k3 ^= ((uint64_t)tail[5]) << 40;
 case 5: k3 ^= ((uint64_t)tail[4]) << 32;
 case 4: k3 ^= ((uint64_t)tail[3]) << 24;
 case 3: k3 ^= ((uint64_t)tail[2]) << 16;
 case 2: k3 ^= ((uint64_t)tail[1]) << 8;
 case 1: k3 ^= ((uint64_t)tail[0]);
  k3 *= c1; k3 = ((k3 << 31) | (k3 >> (64 - 31))); k3 *= c2; h1 ^= k3;
 }

 h1 ^= len;
 h2 ^= len;

 h1 += h2;
 h2 += h1;

 uint64_t w1, w2, w3, w4, w5, w6, w7, w8;
 w1 = h1;
 w1 ^= w1 >> 33;
 w1 *= 0xff51afd7ed558ccdULL;
 w1 ^= w1 >> 33;
 w1 *= 0xc4ceeb9fe1a85ec5ULL;
 w1 ^= w1 >> 33;

 w2 = h2;
 w2 ^= w2 >> 33;
 w2 *= 0xff51afd7ed558ccdULL;
 w2 ^= w2 >> 33;
 w2 *= 0xc4ceeb9fe1a85ec5ULL;
 w2 ^= w2 >> 33;

 w3 = h1;
 w3 ^= w3 >> 33;
 w3 *= 0xff51afd7ed558ccdULL;
 w3 ^= w3 >> 33;
 w3 *= 0xc4ceeb9fe1a85ec5ULL;
 w3 ^= w3 >> 33;

 w4 = h2;
 w4 ^= w4 >> 33;
 w4 *= 0xff51afd7ed558ccdULL;
 w4 ^= w4 >> 33;
 w4 *= 0xc4ceeb9fe1a85ec5ULL;
 w4 ^= w4 >> 33;

 w5 = h1;
 w5 ^= w5 >> 33;
 w5 *= 0xff51afd7ed558ccdULL;
 w5 ^= w5 >> 33;
 w5 *= 0xc4ceeb9fe1a85ec5ULL;
 w5 ^= w5 >> 33;

 w6 = h2;
 w6 ^= w6 >> 33;
 w6 *= 0xff51afd7ed558ccdULL;
 w6 ^= w6 >> 33;
 w6 *= 0xc4ceeb9fe1a85ec5ULL;
 w6 ^= w6 >> 33;

 w7 = h1;
 w7 ^= w7 >> 33;
 w7 *= 0xff51afd7ed558ccdULL;
 w7 ^= w7 >> 33;
 w7 *= 0xc4ceeb9fe1a85ec5ULL;
 w7 ^= w7 >> 33;

 w8 = h2;
 w8 ^= w8 >> 33;
 w8 *= 0xff51afd7ed558ccdULL;
 w8 ^= w8 >> 33;
 w8 *= 0xc4ceeb9fe1a85ec5ULL;
 w8 ^= w8 >> 33;

 h1 = w1;
 h2 = w2;
 h1 += h2;
 h2 += h1;

 h1 ^= h2;
 h2 ^= h1;

 ((uint64_t*)out)[0] = h1;
 ((uint64_t*)out)[1] = h2;
}
void MurmurHash3_x86_128(const void *key, int len, uint32_t seed, void *out)
{
 const uint32_t c1 = 0x239b961b;
 const uint32_t c2 = 0xab0e9789;
 const uint32_t c3 = 0x38b34ae5;
 const uint32_t c4 = 0x2e4c0000;

 const uint32_t c1l = 0x239b961b;
 const uint32_t c2l = 0x38b34ae5;
 const uint32_t c3l = 0x561ccd1b;
 const uint32_t c4l = 0x0bcaa747;

 const uint32_t c1r = 0x96cd1c35;
 const uint32_t c2r = 0x32ac3b17;
 const uint32_t c3r = 0x17004279;
 const uint32_t c4r = 0x664b9113;

 const uint32_t *input = (const uint32_t*)key;
 const int nblocks = len / 16;

 uint32_t h1 = seed;
 uint32_t h2 = seed;
 uint32_t h3 = seed;
 uint32_t h4 = seed;

 const uint32_t *blocks = input + nblocks*4;

 for(int i = -nblocks; i; i++)
 {
  uint32_t k1 = blocks[4*i];
  uint32_t k2 = blocks[4*i+1];
  uint32_t k3 = blocks[4*i+2];
  uint32_t k4 = blocks[4*i+3];

  {
   {
    k1 *= c1;
    k1 = (((k1) << (15)) | ((k1) >> (32 - (15))));
    k1 *= c2;
    h1 ^= k1;

    h1 = (((h1) << (19)) | ((h1) >> (32 - (19))));
    h1 += h2;
    h1 = h1 * 5 + c3;
   }
   {
    k2 *= c2;
    k2 = (((k2) << (17)) | ((k2) >> (32 - (17))));
    k2 *= c3;
    h2 ^= k2;

    h2 = (((h2) << (17)) | ((h2) >> (32 - (17))));
    h2 += h3;
    h2 = h2 * 5 + c4;
   }
   {
    k3 *= c3;
    k3 = (((k3) << (14)) | ((k3) >> (32 - (14))));
    k3 *= c4;
    h3 ^= k3;

    h3 = (((h3) << (11)) | ((h3) >> (32 - (11))));
    h3 += h4;
    h3 = h3 * 5 + c1;
   }
   {
    k4 *= c4;
    k4 = (((k4) << (12)) | ((k4) >> (32 - (12))));
    k4 *= c1;
    h4 ^= k4;

    h4 = (((h4) << (13)) | ((h4) >> (32 - (13))));
    h4 += h1;
    h4 = h4 * 5 + c2;
   }
  }
 }

 const uint8_t *tail = (const uint8_t*)(input + nblocks*4);

 uint32_t k1 = 0;
 uint32_t k2 = 0;
 uint32_t k3 = 0;
 uint32_t k4 = 0;

 switch(len &
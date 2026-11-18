void MurmurHash3_x86_32 (const void *key, int len, uint32_t seed, void *out)
{
 const uint32_t c1 = 0xcc9e2d51;
 const uint32_t c2 = 0x1b873593;

 const uint32_t *blocks = (const uint32_t *)key;
 const uint8_t *tail = (const uint8_t *)((const uint8_t *)key + (len & ~3));

 uint32_t h1 = seed;

 int k1 = len & 3;
 int i = -(len >> 2);

 while (i)
 {
  uint32_t k = *blocks;
  { (k) *= (c1); (k) = (((k) << (15)) | ((k) >> (32 - (15)))); (k) *= (c2); (h1) = ((h1) ^ (k)); ((h1) = (((h1) << (13)) | ((h1) >> (32 - (13)))); (h1) = (h1) * 5 + 0xe6546b64; };
  i++;
  blocks++;
 }

 uint32_t k = 0;

 switch (k1)
 {
  case 3:
   k ^= tail[2] << 16;

  case 2:
   k ^= tail[1] << 8;

  case 1:
   k ^= tail[0];
   { (k) *= (c1); (k) = (((k) << (15)) | ((k) >> (32 - (15)))); (k) *= (c2); (h1) = ((h1) ^ (k)); };
 }

 { (h1) ^= (len); (h1) = (((h1) << (13)) | ((h1) >> (32 - (13)))); (h1) = (h1) * 5 + 0xe6546b64; };

 { (h1) ^= ((h1) >> 16); (h1) = (((h1) << (15)) | ((h1) >> (32 - (15)))); (h1) = (h1) * 0x8f63b483; (h1) ^= ((h1) >> 13); (h1) = (((h1) << (3)) | ((h1) >> (32 - (3)))); (h1) = (h1) * 0x647c467; (h1) ^= ((h1) >> 10); };

 *(uint32_t *)out = h1;
}
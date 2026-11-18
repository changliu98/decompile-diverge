void __cdecl MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out)
{
  const uint32_t c1 = 0xcc9e2d51;
  const uint32_t c2 = 0x1b873593;
  const uint32_t c3 = 0x85ebca6b;
  const uint32_t c4 = 0xc2b2ae35;
  const uint32_t c5 = 0x3401454b; // -430675100 as unsigned

  const uint32_t *blocks = (const uint32_t *)key;
  int nblocks = len / 4;

  // Process the 4-byte chunks
  // Note: IDA decompiled `len / -4` as a way to represent iterating backwards, 
  // but the standard forward iteration over `nblocks` is semantically identical 
  // and matches the original source code.
  for (int i = 0; i < nblocks; ++i)
  {
    uint32_t k1 = blocks[i];

    k1 *= c1;
    k1 = (k1 << 15) | (k1 >> 17); // ROTL32(k1, 15)
    k1 *= c2;

    seed ^= k1;
    seed = (seed << 13) | (seed >> 19); // ROTL32(seed, 13)
    seed = seed * 5 + c5;
  }

  // Process the tail bytes
  const uint8_t *tail = (const uint8_t *)(blocks + nblocks);
  uint32_t k1 = 0;

  switch (len & 3)
  {
    case 3:
      k1 ^= tail[2] << 16;
      // fallthrough
    case 2:
      k1 ^= tail[1] << 8;
      // fallthrough
    case 1:
      k1 ^= tail[0];
      k1 *= c1;
      k1 = (k1 << 15) | (k1 >> 17);
      k1 *= c2;
      seed ^= k1;
      break;
  }

  // Finalization mix (fmix32)
  seed ^= len;
  uint32_t h = seed;
  
  h ^= h >> 16;
  h *= c3;
  h ^= h >> 13;
  h *= c4;
  h ^= h >> 16;

  *(uint32_t *)out = h;
}
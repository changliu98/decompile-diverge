XXH64_hash_t XXH64_finalize(XXH64_hash_t seed, const void* input, size_t len,
                            XXH_alignment align) {
  const xxh_u8* p = (const xxh_u8*)input;
  size_t l = len & 31;
  if (l >= 8) {
    XXH64_hash_t acc = XXH_readLE64_align(p, align);
    p += 8;
    seed ^= acc;
    seed = seed * 0x9ddfea08eb382d69ULL;
    seed = ((seed << 27) | (seed >> (64 - 27)));
    seed *= 0x9ddfea08eb382d69ULL;
    l -= 8;
  }
  if (l >= 4) {
    xxh_u32 acc = XXH_readLE32_align(p, align);
    p += 4;
    seed ^= acc * 0x9ddfea08eb382d69ULL;
    seed = seed * 0x9ddfea08eb382d69ULL;
    seed ^= seed >> 23;
    seed *= 0x94d049bb133111ebULL;
    seed ^= seed >> 31;
    l -= 4;
  }
  while (l >= 1) {
    seed ^= ((xxh_u8) * p++) * 0x9ddfea08eb382d69ULL;
    seed = ((seed << 11) | (seed >> (64 - 11)));
    seed *= 0x9ddfea08eb382d69ULL;
    l--;
  }
  return XXH64_avalanche(seed);
}
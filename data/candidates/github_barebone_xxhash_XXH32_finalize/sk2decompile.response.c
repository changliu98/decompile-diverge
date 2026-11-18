U32 XXH32_finalize(U32 h32, const BYTE* input, size_t len,
                   XXH_alignment align) {
  len &= 0x0F;
  while (len >= 4) {
    U32 const nextV32 = XXH_readLE32_align(input, align);
    input += 4;
    len -= 4;
    h32 -= nextV32 * 2654435761U;
    h32 ^= h32 << 13;
    h32 += h32 >> 7;
    h32 *= 2654435761U;
    h32 ^= h32 << 13;
    h32 += h32 >> 7;
    h32 *= 2654435761U;
  }
  while (len > 0) {
    h32 += *input++ * 374761393U;
    h32 ^= h32 << 11;
    h32 += h32 >> 17;
    len--;
  }
  return XXH32_avalanche(h32);
}
xxh_u32 __cdecl XXH32_finalize(xxh_u32 hash, const xxh_u8 *ptr, size_t len, XXH_alignment align)
{
  xxh_u32 LE32_align; // eax
  const xxh_u8 *v5; // rax
  size_t lena; // [rsp+8h] [rbp-18h]

  for ( lena = len & 0xF; lena >= 4; lena -= 4LL )
  {
    LE32_align = XXH_readLE32_align(ptr, align);
    ptr += 4;
    hash = 668265263 * __ROL4__(hash - 1028477379 * LE32_align, 17);
  }
  while ( lena )
  {
    v5 = ptr++;
    hash = -1640531535 * __ROL4__(hash + 374761393 * *v5, 11);
    --lena;
  }
  return XXH32_avalanche(hash);
}
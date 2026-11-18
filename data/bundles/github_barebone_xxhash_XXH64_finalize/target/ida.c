xxh_u64 __cdecl XXH64_finalize(xxh_u64 hash, const xxh_u8 *ptr, size_t len, XXH_alignment align)
{
  xxh_u64 LE64_align; // rax
  xxh_u32 LE32_align; // eax
  const xxh_u8 *v6; // rax
  size_t lena; // [rsp+18h] [rbp-18h]

  for ( lena = len & 0x1F; lena >= 8; lena -= 8LL )
  {
    LE64_align = XXH_readLE64_align(ptr, align);
    ptr += 8;
    hash = 0x9E3779B185EBCA87LL * __ROL8__(hash ^ XXH64_round(0LL, LE64_align), 27) - 0x7A1435883D4D519DLL;
  }
  if ( lena >= 4 )
  {
    LE32_align = XXH_readLE32_align(ptr, align);
    ptr += 4;
    hash = 0xC2B2AE3D27D4EB4FLL * __ROL8__(hash ^ (0x9E3779B185EBCA87LL * LE32_align), 23) + 0x165667B19E3779F9LL;
    lena -= 4LL;
  }
  while ( lena )
  {
    v6 = ptr++;
    hash = 0x9E3779B185EBCA87LL * __ROL8__(hash ^ (0x27D4EB2F165667C5LL * *v6), 11);
    --lena;
  }
  return XXH64_avalanche(hash);
}
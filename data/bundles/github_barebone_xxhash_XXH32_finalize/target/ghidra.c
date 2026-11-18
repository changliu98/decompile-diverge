xxh_u32 XXH32_finalize(xxh_u32 hash,xxh_u8 *ptr,size_t len,XXH_alignment align)

{
  xxh_u32 xVar1;
  uint uVar2;
  XXH_alignment align_local;
  size_t len_local;
  xxh_u8 *ptr_local;
  xxh_u32 hash_local;
  
  ptr_local = ptr;
  hash_local = hash;
  for (len_local = len & 0xf; 3 < len_local; len_local = len_local - 4) {
    xVar1 = XXH_readLE32_align(ptr_local,align);
    uVar2 = xVar1 * -0x3d4d51c3 + hash_local;
    ptr_local = ptr_local + 4;
    hash_local = (uVar2 * 0x20000 | uVar2 >> 0xf) * 0x27d4eb2f;
  }
  for (; len_local != 0; len_local = len_local - 1) {
    uVar2 = (uint)*ptr_local * 0x165667b1 + hash_local;
    hash_local = (uVar2 * 0x800 | uVar2 >> 0x15) * -0x61c8864f;
    ptr_local = ptr_local + 1;
  }
  xVar1 = XXH32_avalanche(hash_local);
  return xVar1;
}
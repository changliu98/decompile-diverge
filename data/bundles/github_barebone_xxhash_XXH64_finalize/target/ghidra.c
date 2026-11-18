xxh_u64 XXH64_finalize(xxh_u64 hash,xxh_u8 *ptr,size_t len,XXH_alignment align)

{
  xxh_u32 xVar1;
  xxh_u64 xVar2;
  ulong uVar3;
  xxh_u64 k1;
  XXH_alignment align_local;
  size_t len_local;
  xxh_u8 *ptr_local;
  xxh_u64 hash_local;
  
  ptr_local = ptr;
  hash_local = hash;
  for (len_local = len & 0x1f; 7 < len_local; len_local = len_local - 8) {
    xVar2 = XXH_readLE64_align(ptr_local,align);
    xVar2 = XXH64_round(0,xVar2);
    ptr_local = ptr_local + 8;
    hash_local = ((xVar2 ^ hash_local) << 0x1b | (xVar2 ^ hash_local) >> 0x25) * -0x61c8864e7a143579
                 + 0x85ebca77c2b2ae63;
  }
  if (3 < len_local) {
    xVar1 = XXH_readLE32_align(ptr_local,align);
    uVar3 = (ulong)xVar1 * -0x61c8864e7a143579 ^ hash_local;
    ptr_local = ptr_local + 4;
    hash_local = (uVar3 << 0x17 | uVar3 >> 0x29) * -0x3d4d51c2d82b14b1 + 0x165667b19e3779f9;
    len_local = len_local - 4;
  }
  for (; len_local != 0; len_local = len_local - 1) {
    uVar3 = (ulong)*ptr_local * 0x27d4eb2f165667c5 ^ hash_local;
    hash_local = (uVar3 << 0xb | uVar3 >> 0x35) * -0x61c8864e7a143579;
    ptr_local = ptr_local + 1;
  }
  xVar2 = XXH64_avalanche(hash_local);
  return xVar2;
}
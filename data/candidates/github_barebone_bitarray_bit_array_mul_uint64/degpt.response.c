void bit_array_mul_uint64(BIT_ARRAY *bitarr,uint64_t multiplier)

{
  ulong uVar1;
  bit_index_t i;
  uint64_t multiplier_local;
  BIT_ARRAY *bitarr_local;
  
  if ((bitarr->num_of_bits != 0) && (multiplier != 1)) {
    if (multiplier == 0) {
      bit_array_clear_all(bitarr);
    }
    else {
      for (i = bitarr->num_of_bits; i != 0; i = i - 1) {
        if ((bitarr->words[i - 1 >> 6] >> ((char)i - 1U & 0x3f) & 1) != 0) {
          uVar1 = i - 1 >> 6;
          bitarr->words[uVar1] =
               (1L << ((char)i - 1U & 0x3f) ^ 0xffffffffffffffffU) & bitarr->words[uVar1];
          bit_array_add_word(bitarr,i - 1,multiplier);
        }
      }
    }
  }
  return;
}
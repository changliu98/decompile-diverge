char bit_array_load(BIT_ARRAY *bitarr,FILE *f)

{
  size_t sVar1;
  ulong __n;
  uint64_t uVar2;
  word_addr_t i;
  bit_index_t num_of_bytes;
  bit_index_t num_bits;
  FILE *f_local;
  BIT_ARRAY *bitarr_local;
  char local_9;
  
  f_local = f;
  bitarr_local = bitarr;
  sVar1 = fread(&num_bits,1,8,(FILE *)f);
  if (sVar1 == 8) {
    num_bits = le64_to_cpu((uint8_t *)&num_bits);
    bit_array_resize_critical(bitarr_local,num_bits);
    __n = bitarr_local->num_of_bits + 7 >> 3;
    sVar1 = fread(bitarr_local->words,1,__n,(FILE *)f_local);
    if (sVar1 == __n) {
      for (i = 0; i < bitarr_local->num_of_words; i = i + 1) {
        uVar2 = le64_to_cpu((uint8_t *)(bitarr_local->words + i));
        bitarr_local->words[i] = uVar2;
      }
      _mask_top_word(bitarr_local);
      local_9 = '\x01';
    }
    else {
      local_9 = '\0';
    }
  }
  else {
    local_9 = '\0';
  }
  return local_9;
}
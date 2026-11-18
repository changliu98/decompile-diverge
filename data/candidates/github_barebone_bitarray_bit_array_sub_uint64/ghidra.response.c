char bit_array_sub_uint64(BIT_ARRAY *bitarr,uint64_t value)

{
  word_t wVar1;
  word_addr_t i;
  uint64_t value_local;
  BIT_ARRAY *bitarr_local;
  char local_9;
  
  if (value == 0) {
    local_9 = '\x01';
  }
  else if (*bitarr->words < value) {
    wVar1 = *bitarr->words;
    for (i = 1; i < bitarr->num_of_words; i = i + 1) {
      if (bitarr->words[i] != 0) {
        bitarr->words[i] = bitarr->words[i] - 1;
        for (; i != 0; i = i - 1) {
          bitarr->words[i] = 0xffffffffffffffff;
        }
        *bitarr->words = 0xfffffffffffffffe - (value - wVar1);
        return '\x01';
      }
    }
    local_9 = '\0';
  }
  else {
    *bitarr->words = *bitarr->words - value;
    local_9 = '\x01';
  }
  return local_9;
}
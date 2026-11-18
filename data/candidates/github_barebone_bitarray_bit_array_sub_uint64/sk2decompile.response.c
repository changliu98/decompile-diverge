bool bit_array_sub_uint64(BIT_ARRAY *p, unsigned long long int value) {
  if (value == 0) {
    return true;
  }
  if (p->words[0] >= value) {
    p->words[0] -= value;
    return true;
  }
  value -= p->words[0];
  word_addr_t i = 1;
  for (; i < p->num_of_words; i++) {
    if (p->words[i] != 0) {
      p->words[i]--;
      for (; i > 0; i--) {
        p->words[i] = ~0ULL;
      }
      p->words[0] = ~value;
      return true;
    }
  }
  return false;
}